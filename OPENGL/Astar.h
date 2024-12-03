#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include "Time.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Map.h"
//
//struct Node {
//    int x , y;
//    float g , h , f;
//    Node* parent;
//
//    bool operator>( const Node& other ) const {
//        return f > other.f;
//    }
//};
//
//class AStar {
//private:
//    float heuristic ( const Node& a , const Node& b ) {
//        return sqrt ( pow ( b.x - a.x , 2 ) + pow ( b.y - a.y , 2 ) ); // 유클리드 거리
//    }
//
//public:
//    std::vector<int> findPath ( const Graph& graph , int start , int goal ) {
//        std::vector<float> gCost ( graph.nodeCount ( ) , std::numeric_limits<float>::infinity ( ) );
//        std::vector<float> fCost ( graph.nodeCount ( ) , std::numeric_limits<float>::infinity ( ) );
//        std::unordered_map<int , int> cameFrom;
//
//        auto cmp = [&fCost]( int left , int right ) { return fCost[ left ] > fCost[ right ]; };
//        std::priority_queue<int , std::vector<int> , decltype( cmp )> openSet ( cmp );
//
//        gCost[ start ] = 0.0f;
//        fCost[ start ] = heuristic ( graph.getNode ( start ) , graph.getNode ( goal ) );
//        openSet.push ( start );
//
//        while ( !openSet.empty ( ) ) {
//            int current = openSet.top ( );
//            openSet.pop ( );
//
//            if ( current == goal ) {
//                std::vector<int> path;
//                while ( cameFrom.find ( current ) != cameFrom.end ( ) ) {
//                    path.push_back ( current );
//                    current = cameFrom[ current ];
//                }
//                path.push_back ( start );
//                std::reverse ( path.begin ( ) , path.end ( ) );
//                return path;
//            }
//
//            for ( int neighbor : graph.getNeighbors ( current ) ) {
//                const Node& currentNode = graph.getNode ( current );
//                const Node& neighborNode = graph.getNode ( neighbor );
//
//                if ( !neighborNode.walkable ) continue;
//
//                float tentativeGCost = gCost[ current ] + heuristic ( currentNode , neighborNode );
//
//                if ( tentativeGCost < gCost[ neighbor ] ) {
//                    cameFrom[ neighbor ] = current;
//                    gCost[ neighbor ] = tentativeGCost;
//                    fCost[ neighbor ] = gCost[ neighbor ] + heuristic ( neighborNode , graph.getNode ( goal ) );
//
//                    openSet.push ( neighbor );
//                }
//            }
//        }
//
//        return {}; // 경로를 찾지 못한 경우
//    }
//};

struct Node {
    int x , y;
    float g , h , f;
    Node* parent;

    bool operator>( const Node& other ) const {
        return f > other.f;
    }
};

const float distance = 49.0f;

class Astar {





    // 2D 맵 (0은 통과 가능, 1은 장애물, 3은 플레이어는 가지만 적은 못감 4는 문)
    std::vector<std::vector<int>> grid = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,3,3,3,1,1,1,3,3,3,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1},
  {1,1,1,1,1,1,3,0,3,1,1,1,3,0,3,1,1,1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1},
  {1,1,1,1,1,1,3,0,3,1,1,1,3,0,3,1,1,1,1,1,1,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,3,1},
  {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,3,3,0,3,1,1,1,1,1,1,1,1,1,1,1,1,3,0,3,1},
  {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,3,0,3,1},
  {1,1,1,1,1,1,2,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,3,0,3,1},
  {1,1,1,1,1,1,2,0,2,0,0,0,0,2,0,0,0,2,0,0,0,0,0,2,1,1,1,1,1,1,3,3,3,3,3,1,3,0,3,1},
  {1,1,1,1,1,1,2,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,3,0,0,0,0,1,3,0,3,1},
  {1,1,1,1,1,1,2,0,2,0,0,0,0,2,0,0,0,0,2,2,2,0,0,2,1,1,1,1,1,1,3,0,0,3,0,1,3,0,3,1},
  {1,1,1,1,1,1,1,1,1,3,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,0,3,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,3,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,3,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,3,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,3,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,3,1,0,0,0,0,0,1},
  {1,1,1,1,1,1,0,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,3,1,0,0,0,0,0,1},
  {3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1,0,0,2,0,0,3,1,2,2,2,2,2,1},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1,0,0,0,0,0,3,1,2,2,2,2,2,1},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,1,0,0,0,0,0,3,1,2,2,2,2,2,1},
  {3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,1,1,0,0,3,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,0,2,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,3,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,3,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,3,1,1,1,3,0,3,1},
  {1,1,1,1,1,1,1,1,1,3,4,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1,1,1,3,0,3,1},
  {1,1,1,1,1,1,1,1,1,3,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,3,1,1,1,3,0,3,1},
  {1,1,1,1,1,1,1,1,1,3,0,3,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,3,3,3,3,3,0,3,1},
  {1,1,1,1,1,1,1,1,1,3,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,3,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,3,3,3,3,3,3,3,1},
  {1,1,1,1,1,1,3,0,0,0,0,0,0,0,0,1,1,1,3,3,3,3,3,3,3,3,3,1,1,1,0,0,3,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,3,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,3,1,1,1,0,0,3,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,3,0,0,0,0,0,0,0,0,1,1,1,0,0,3,3,3,3,3,0,3,1,1,1,0,0,3,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,3,0,3,1,1,1,0,0,0,0,0,0,0,0,3,1,1,1,3,0,3,3,3,3,3,0,3,3,3,3,3,3,4,1},
  {1,1,1,1,1,1,3,0,3,1,1,1,0,0,0,0,0,0,0,0,3,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1},
  {1,1,1,1,1,1,3,0,3,1,1,1,3,3,3,3,3,3,3,3,3,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,1},
  {1,1,1,3,3,3,3,0,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,3,0,0,0,0,0,0,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,3,0,3,3,3,3,3,0,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,3,0,3,1,1,1,3,0,3,3,3,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,3,0,3,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,1,1,3,3,3,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

    };
    
    bool mapMa[ 25 ][ 25 ] = {};
    float renewTime = 0.0f;
    glm::ivec2 start = { 0,0 };
    glm::ivec2 goal = { 4,4 };
    
    int goalX = 0 , goalY = 4;
    int startX = 0 , startY = 0;
   
    // 경로 캐싱
    std::vector<std::tuple<int , int>> cachedPath;
    int cachedGoalX = -1 , cachedGoalY = -1;

public: // 휴리스틱 함수 ( 맨해튼 거리 )
    Astar ( ) {

    }

    std::vector<std::tuple<int , int>> path;

    float heuristic ( int x1 , int y1 , int x2 , int y2 ) {
        return std::abs ( x1 - x2 ) + std::abs ( y1 - y2 );
    }

    // 동적 A* 알고리즘
    std::vector<std::tuple<int , int>> dynamicAStar (int startX , int startY ,int goalX , int goalY ,
        const std::vector<std::vector<int>>& grid );

    void Path_now ( glm::vec3 Pos , glm::ivec2& path_now );




    std::vector<std::tuple<int , int>>  A_star ( ) {


        // 초기 경로 계산
        path = dynamicAStar ( start.x , start.y , goal.x , goal.y , grid );

        // 경로 출력
        if ( !path.empty ( ) ) {
            std::cout << "Path found:\n";
            for ( const auto& [x , y] : path ) {
                std::cout << "(" << x << ", " << y << ") ";
            }
            std::cout << std::endl;
        }
        else {
            std::cout << "No path found.\n";
        }

       

        return path;
    }
    
  
    bool RenewTime ( ) {
        renewTime += Time::DeltaTime ( );

        
        if ( renewTime > 0.3f  ) {
            glm::vec3 p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );

            glm::vec3 p2 = CollisionManager::getInstance ( ).ReturnMonster ( );
            Path_now ( p2 , start );


            glm::ivec2 origin_goal = goal;
            Path_now ( p1 , goal );

            

           
           if ( goal == origin_goal || goal.x < 0 || goal.y < 0 || grid[ goal.y ][ goal.x ] != 0 ) {
                return false;
            }
                if ( renewTime > 8.0f ) {
                    renewTime = 0.0f;
                    path.clear ( );

                    glm::vec3 p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );

                    glm::vec3 p2 = CollisionManager::getInstance ( ).ReturnMonster ( );

                    Path_now ( p1 , goal );

                    Path_now ( p2 , start );

                   
                }

            
                return true;
        }
        
        return false;
    }

    bool RenewTime2 (glm::ivec2 _path ) {
        glm::vec3 p2 = CollisionManager::getInstance ( ).ReturnMonster ( );

        renewTime += Time::DeltaTime ( );


        if ( renewTime > 0.3f ) {
            glm::vec3 p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );
            glm::vec3 p2 = CollisionManager::getInstance ( ).ReturnMonster ( );
            Path_now ( p2 , start );


            glm::ivec2 origin_goal = goal;
            goal = _path;


            //if ( distance >= ( ( p2.x - p1.x ) * ( p2.x - p1.x ) ) + ( ( p2.z - p1.z ) * ( p2.z - p1.z ) ) ) {
            //    renewTime = 0.0f;

            //    Path_now ( p1 , goal );
            //    path.clear ( );

            //}
               if ( goal == origin_goal || goal.x<0 || goal.y < 0 ||grid[goal.y][goal.x] != 0 ) {
                   return false;
               }
               

            
               return true;
        }


        return false;
    }
    

};



