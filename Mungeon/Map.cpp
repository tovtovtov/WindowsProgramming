#include "Map.h"

Map::Map()
{
	m_width = 0;
	m_height = 0;

	random_device rd;
	random.seed(rd());
}

void Map::CarveMaze(int x, int y)
{
    // 상, 하, 좌, 우
    int dx[4] = { 0, 0, -2, 2 };
    int dy[4] = { -2, 2, 0, 0 };

    // 방향 순서를 무작위로 섞음
    vector<int> directions = { 0, 1, 2, 3 };

    shuffle(
        directions.begin(),
        directions.end(),
        random
    );

    for (int dir : directions)
    {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // 맵 범위 확인
        if (nx <= 0 || nx >= m_width - 1 ||
            ny <= 0 || ny >= m_height - 1)
        {
            continue;
        }

        // 이미 방문한 위치인지 확인
        if (m_mapData[ny][nx] == 0)
        {
            continue;
        }

        // 중간 벽 제거
        m_mapData[y + dy[dir] / 2]
            [x + dx[dir] / 2] = 0;

        // 이동한 위치를 바닥으로 변경
        m_mapData[ny][nx] = 0;

        // 다음 위치에서 반복
        CarveMaze(nx, ny);
    }
}

void Map::ConnectPaths(MazeDifficulty diff)
{
    int connectRate = 15;

    if (diff == EASY)
        connectRate = 50;

    else if (diff == NORMAL)
        connectRate = 15;

    else if (diff == HARD)
        connectRate = 10;

    uniform_int_distribution<int> chance(1, 100);

    // 맵 내부의 벽 검사
    for (int y = 1; y < m_height - 1; y++)
    {
        for (int x = 1; x < m_width - 1; x++)
        {
            // 이미 바닥이면 건너뜀
            if (m_mapData[y][x] == 0)
                continue;

            // 좌우 바닥이 연결되어 있는 벽
            bool horizontal =
                m_mapData[y][x - 1] == 0 &&
                m_mapData[y][x + 1] == 0;

            // 상하 바닥이 연결되어 있는 벽
            bool vertical =
                m_mapData[y - 1][x] == 0 &&
                m_mapData[y + 1][x] == 0;

            if (horizontal || vertical)
            {
                if (chance(random) <= connectRate)
                {
                    RemoveWall(x, y);
                }
            }
        }
    }
}

void Map::RemoveWall(int x, int y)
{
    m_mapData[y][x] = 0;
}

// 미로 생성 시작
void Map::GenerateMaze(
    int width,
    int height,
    MazeDifficulty diff,
    unsigned int seed
)
{
    // 홀수 크기인지 확인
    if (width < 3 || height < 3 ||
        width % 2 == 0 || height % 2 == 0)
    {
        return;
    }

    this->m_width = width;
    this->m_height = height;

    // 랜덤 시드 설정
    random.seed(seed);

    // 전체 맵을 벽으로 초기화
    m_mapData.assign(height, vector<int>(width, 1));

    // 시작 위치
    m_mapData[1][1] = 0;

    // 기본 미로 생성
    CarveMaze(1, 1);

    // 추가 통로 연결
    ConnectPaths(diff);
}

void Map::Render(HDC hdc, ResourceManager* resource)
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            if (m_mapData[y][x] == 0)
            {
                // 바닥 타일
                resource->DrawImage(
                    hdc, "maptile",
                    x, y,
                    1, 1,
                    3, 11, 32, 32
                );
            }
            else if (m_mapData[y][x] == 1)
            {
                // 벽 타일
                resource->DrawImage(
                    hdc, "maptile",
                    x, y,
                    1, 1,
                    0, 3, 32, 32
                );
            }
        }
    }
}


