#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility> // for std::pair

// 노드 구조체 정의
struct Node {
    float x , y; // 노드의 월드 좌표
    bool walkable; // 이동 가능 여부

    Node ( float x , float y , bool walkable = true ) : x ( x ) , y ( y ) , walkable ( walkable ) {}
};

// 그래프 클래스
class Create_Graph {
private:
    std::vector<Node> nodes; // 노드 리스트
    std::unordered_map<int , std::vector<int>> edges; // 노드 간 엣지 (인접 리스트)

public:
    // 그래프 생성 함수
    void generate ( float worldWidth , float worldHeight , float cellSize ) {
        int rows = worldHeight / cellSize;
        int cols = worldWidth / cellSize;

        // 노드 생성
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                float x = j * cellSize + cellSize / 2.0f; // 셀 중심점 x 좌표
                float y = i * cellSize + cellSize / 2.0f; // 셀 중심점 y 좌표
                nodes.emplace_back ( x , y ); // 노드 추가
            }
        }

        // 엣지 생성
        for ( int i = 0; i < rows; ++i ) {
            for ( int j = 0; j < cols; ++j ) {
                int currentNodeIndex = i * cols + j;

                // 4방향(상하좌우) 연결
                if ( i > 0 ) edges[ currentNodeIndex ].push_back ( ( i - 1 ) * cols + j ); // 위
                if ( i < rows - 1 ) edges[ currentNodeIndex ].push_back ( ( i + 1 ) * cols + j ); // 아래
                if ( j > 0 ) edges[ currentNodeIndex ].push_back ( i * cols + ( j - 1 ) ); // 왼쪽
                if ( j < cols - 1 ) edges[ currentNodeIndex ].push_back ( i * cols + ( j + 1 ) ); // 오른쪽
            }
        }
    }

    // 장애물 추가 (노드 제거)
    void addObstacle ( float x , float y , float cellSize ) {
        for ( int i = 0; i < nodes.size ( ); ++i ) {
            if ( abs ( nodes[ i ].x - x ) < cellSize / 2.0f && abs ( nodes[ i ].y - y ) < cellSize / 2.0f ) {
                nodes[ i ].walkable = false; // 이동 불가능 설정
                edges.erase ( i ); // 엣지 제거
            }
        }
    }

    // 그래프 디버그 출력
    void print ( ) const {
        for ( int i = 0; i < nodes.size ( ); ++i ) {
            std::cout << "Node " << i << " (" << nodes[ i ].x << ", " << nodes[ i ].y << ")";
            if ( !nodes[ i ].walkable ) std::cout << " [Obstacle]";
            std::cout << " -> ";
            if ( edges.count ( i ) ) {
                for ( int neighbor : edges.at ( i ) ) {
                    std::cout << neighbor << " ";
                }
            }
            std::cout << "\n";
        }
    }
};

