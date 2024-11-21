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

const float distance = 900.0f;

class Astar {

    // 2D 맵 (0은 통과 가능, 1은 장애물)
    std::vector<std::vector<int>> grid = {
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
    
    bool mapMa[ 25 ][ 25 ] = {};
    float renewTime = 0.0f;
    glm::ivec2 start = { 0,0 };
    glm::ivec2 goal = { 4,4 };
    
    int goalX = 0 , goalY = 4;
    int startX = 0 , startY = 0;
   
public: // 휴리스틱 함수 ( 맨해튼 거리 )
    Astar ( ) {

    }

    std::vector<std::tuple<int , int>> path;

    float heuristic ( int x1 , int y1 , int x2 , int y2 ) {
        return std::abs ( x1 - x2 ) + std::abs ( y1 - y2 );
    }

    // 경로 캐싱
    std::vector<std::tuple<int , int>> cachedPath;
    int cachedGoalX = -1 , cachedGoalY = -1;

    // 동적 A* 알고리즘
    std::vector<std::tuple<int , int>> dynamicAStar (
        int startX , int startY ,
        int goalX , int goalY ,
        const std::vector<std::vector<int>>& grid ) {

        // 목표 위치가 이전과 같으면 캐시된 경로 반환
        if ( cachedGoalX == goalX && cachedGoalY == goalY ) {
            return cachedPath;
        }

        // A* 알고리즘 실행
        std::priority_queue<Node , std::vector<Node> , std::greater<Node>> openList;
        std::unordered_map<int , Node*> closedList;

        auto index = [&]( int x , int y ) {
            return y * grid[ 0 ].size ( ) + x;
            };

        openList.push ( { startX, startY, 0, heuristic ( startX, startY, goalX, goalY ), 0, nullptr } );

        while ( !openList.empty ( ) ) {
            Node current = openList.top ( );
            openList.pop ( );

            // 목표 지점에 도달하면 경로 복원
            if ( current.x == goalX && current.y == goalY ) {
                std::vector<std::tuple<int , int>> path;
                Node* n = &current;
                while ( n ) {
                    path.emplace_back ( n->x , n->y );
                    n = n->parent;
                }
                std::reverse ( path.begin ( ) , path.end ( ) );

                // 경로 캐시 갱신
                cachedPath = path;
                cachedGoalX = goalX;
                cachedGoalY = goalY;

                return path;
            }

            closedList[ index ( current.x , current.y ) ] = new Node ( current );

            // 이웃 탐색 (상하좌우)
            std::vector<std::tuple<int , int>> directions = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
            for ( auto& dir : directions ) {
                int nx = current.x + std::get<0> ( dir );
                int ny = current.y + std::get<1> ( dir );

                // 범위 및 장애물 검사
                if ( nx < 0 || ny < 0 || nx >= grid[ 0 ].size ( ) || ny >= grid.size ( ) || grid[ ny ][ nx ] == 1 ) {
                    continue;
                }

                if ( closedList.count ( index ( nx , ny ) ) ) {
                    continue; // 이미 처리된 노드
                }

                float g = current.g + 1;
                float h = heuristic ( nx , ny , goalX , goalY );
                openList.push ( { nx, ny, g, h, g + h, closedList[ index ( current.x, current.y ) ] } );
            }
        }

        return {}; // 경로 없음
    }




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

    void Path_now (glm::vec3 Pos, glm::ivec2& path_now ) {
		//float dul = Pos.x - int ( Pos.x );

		path_now.x = ( int ( Pos.x ) - ( int ( Pos.x ) % 3 ) ) / 3;
		// Z축 인덱스 계산
		path_now.y = ( int ( Pos.z ) / 3 ) * 1; // 기본적으로 3의 배수로 변환
		if ( Pos.z > 0 && int ( Pos.z ) % 3 != 0 ) {
			path_now.y += 1; // 양수 방향 보정

		}
		path_now.y = -path_now.y;


		if ( Pos.x < 0 ) {
			path_now.x -= 1;

		}



		std::cout << "path_now_x : " << path_now.x << std::endl;
		std::cout << "path_now_z : " << path_now.y << std::endl;
		//std::cout <<"iint pos"<< int ( Pos.x ) << std::endl;
	}

    bool RenewTime ( ) {
        renewTime += Time::DeltaTime ( );

        
        if ( renewTime > 1.0f  ) {
            glm::vec3 p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );

            glm::vec3 p2 = CollisionManager::getInstance ( ).ReturnMonster ( );
            Path_now ( p2 , start );


            glm::ivec2 origin_goal = goal;
            Path_now ( p1 , goal );
            if ( goal == origin_goal || goal.x <0 || goal.y<0 ) {
                return false;
            }

            if ( distance >= ( ( p2.x - p1.x ) * ( p2.x - p1.x ) ) + ( ( p2.z - p1.z ) * ( p2.z - p1.z ) ) ) {
                renewTime = 0.0f;
                path.clear ( );
                return true;
            }
            else {
                if ( renewTime > 8.0f ) {
                    renewTime = 0.0f;
                    path.clear ( );

                    glm::vec3 p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );

                    glm::vec3 p2 = CollisionManager::getInstance ( ).ReturnMonster ( );

                    Path_now ( p1 , goal );

                    Path_now ( p2 , start );

                    return true;
                }

            }



         /*   renewTime = 0.0f;
            
            glm::vec3 p1 = CollisionManager::getInstance ( ).ReturnPlayer ( );

            glm::vec3 p2 = CollisionManager::getInstance ( ).ReturnMonster ( );*/

           

            //goal.x = 4;
            //goal.y=4;
            //goal.x = 4; p1.x;
            //goal.y = 4;//pl.y;
            //std::cout << goal.x << std::endl;
            //std::cout << goal.y << std::endl;
            //start.x = p2.x;
            //start.y = p2.y;

        }

        

        return false;
    }

    

};



