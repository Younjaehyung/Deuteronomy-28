#include "Astar.h"
void Astar::Path_now ( glm::vec3 Pos , glm::ivec2& path_now ) {
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

// 동적 A* 알고리즘
std::vector<std::tuple<int , int>> Astar:: dynamicAStar (
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