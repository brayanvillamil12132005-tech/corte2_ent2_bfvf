#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Twitter {
private:
    int timestamp;
    
    // Almacena los tweets de cada usuario: userId -> lista de pares (timestamp, tweetId)
    unordered_map<int, vector<pair<int, int>>> tweets;
    
    // Almacena a quién sigue cada usuario: followerId -> conjunto de followeeIds
    unordered_map<int, unordered_set<int>> follows;

public:
    Twitter() : timestamp(0) {}
    
    void postTweet(int userId, int tweetId) {
        // Guardamos el tweet asociándolo con el tiempo global actual
        tweets[userId].push_back({timestamp++, tweetId});
    }
    
    vector<int> getNewsFeed(int userId) {
        // Max-heap para ordenar los tweets por el timestamp más reciente
        priority_queue<pair<int, int>> maxHeap;
        
        // El usuario siempre debe ver sus propios tweets
        unordered_set<int> userFollows = follows[userId];
        userFollows.insert(userId);
        
        // Recorremos los tweets de todos los usuarios seguidos (y del propio usuario)
        for (int followeeId : userFollows) {
            const auto& userTweets = tweets[followeeId];
            int count = 0;
            // Tomamos como máximo los últimos 10 tweets de cada persona
            for (int i = (int)userTweets.size() - 1; i >= 0 && count < 10; --i) {
                maxHeap.push(userTweets[i]);
                count++;
            }
        }
        
        // Extraemos los 10 tweets más recientes globalmente
        vector<int> feed;
        while (!maxHeap.empty() && feed.size() < 10) {
            feed.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        
        return feed;
    }
    
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            follows[followerId].insert(followeeId);
        }
    }
    
    void unfollow(int followerId, int followeeId) {
        follows[followerId].erase(followeeId);
    }
};

void printFeed(const vector<int>& feed) {
    cout << "[";
    for (size_t i = 0; i < feed.size(); ++i) {
        cout << feed[i] << (i + 1 < feed.size() ? ", " : "");
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== 01. LEETCODE 355: DESIGN TWITTER ===" << endl;
    
    Twitter twitter;

    // Pruebas según el ejemplo oficial
    cout << "\n1. Usuario 1 publica el tweet 5..." << endl;
    twitter.postTweet(1, 5);
    cout << "Feed Usuario 1: ";
    printFeed(twitter.getNewsFeed(1)); // Esperado: [5]

    cout << "\n2. Usuario 1 empieza a seguir a Usuario 2..." << endl;
    twitter.follow(1, 2);

    cout << "\n3. Usuario 2 publica el tweet 6..." << endl;
    twitter.postTweet(2, 6);
    cout << "Feed Usuario 1: ";
    printFeed(twitter.getNewsFeed(1)); // Esperado: [6, 5]

    cout << "\n4. Usuario 1 deja de seguir a Usuario 2..." << endl;
    twitter.unfollow(1, 2);
    cout << "Feed Usuario 1: ";
    printFeed(twitter.getNewsFeed(1)); // Esperado: [5]

    return 0;
}