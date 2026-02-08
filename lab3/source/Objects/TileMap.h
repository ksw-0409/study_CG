#ifndef TILEMAP
#define TILEMAP

#include<vector>
#include<glm/glm.hpp>

// 타일 전용 구조체 (가볍게 유지)
struct TileData {
    glm::vec4 uv;
    int id;
};

// 타일맵 클래스 
class TileMap {
    std::vector<TileData> tileSet; // 인덱스별 UV 정보 저장
public:
    void AddTile(int id, glm::vec4 uv) {
        if (id >= tileSet.size()) tileSet.resize(id + 1);
        tileSet[id] = { uv, id };
    }
};
#endif // TILEMAP