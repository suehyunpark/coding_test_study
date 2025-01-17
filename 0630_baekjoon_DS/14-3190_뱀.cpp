/* #include <iostream>
#include <vector>
#include <deque>
#define APPLE 1
#define SNAKE -1

int main() {
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

    int n, k, l;
    std::cin >> n >> k; // board size -> number of apples
    int map[101][101] = {0,}; // 1~100
    map[1][1] = SNAKE;

    for (int i=0; i<k; ++i) {
        int row, column;
        std::cin >> row >> column;
        map[row][column] = APPLE; // mark apple pos
    }

    std::cin >> l;
    std::vector<std::pair<int,char>> directions;

    for (int i=0; i<l; ++i) {
        int x; char c;
        std::cin >> x >> c;
        directions.push_back({ x, c });
    }

    return 0;
} */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/* 변수 선언 */
struct Pos // 위치 정보 자료형
{
    int y, x;
};
struct Dir // 방향 전환 정보 자료형
{
    int t;
    char d;
};
struct Joint // 뱀의 꺾인 부분 자료형
{
    int y, x, d;
};
int board[101][101]; // 2차원 보드 배열
int n, k, l;
// 방향 : 0 왼쪽, 1 위 ,2 오른쪽, 3 아래
int dy[4] = {0, -1, 0, 1};
int dx[4] = {-1, 0, 1, 0};
queue<Dir> direction;

// 입력
void input()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k;
    int y, x;
    while (k--)
    {
        cin >> y >> x;
        board[y][x] = 2;
    }
    cin >> l;
    int t;
    char d;
    while (l--)
    {
        cin >> t >> d;
        direction.push({t, d});
    }
}

// 오른쪽 회전
int turnRight(int d)
{
    d += 1;
    d = d >= 4 ? d - 4 : d;
    return d;
}

// 왼쪽 회전
int turnLeft(int d)
{
    d -= 1;
    d = d < 0 ? d + 4 : d;
    return d;
}

// 벽이나 자신에게 부딪힌 경우 true 반환
bool isEnd(int y, int x)
{
    // 벽에 부딪힌 경우
    if (y > n || y <= 0 || x > n || x <= 0)
    {
        return true;
    }
    // 자신과 부딪힌 경우
    if (board[y][x] == 1)
    {
        return true;
    }
    return false;
}

// 결과 값 출력
void solve()
{
    int t = 0;                        // 결과 값
    int head_dir = 2, tail_dir = 2;   // 초기 방향 오른쪽
    Pos head = {1, 1}, tail = {1, 1}; // 머리와 꼬리의 위치 정보
    queue<Joint> joint;               // 꺾인 부분 저장하는 큐
    board[1][1] = 1;                  // 왼쪽 위 시작
    while (true)
    {
        t++;
        // 머리의 이동
        head.y += dy[head_dir];
        head.x += dx[head_dir];

        // 부딪힌 경우 break;
        if (isEnd(head.y, head.x))
            break;

        // 머리가 간 곳에 사과가 없으면 꼬리 한 칸 땡기기
        if (board[head.y][head.x] != 2)
        {
            board[tail.y][tail.x] = 0;
            tail.y += dy[tail_dir];
            tail.x += dx[tail_dir];
        }
        board[head.y][head.x] = 1; // 머리가 이동 한 곳 1로 치환

        // 머리 방향 전환
        if (!direction.empty() && t == direction.front().t)
        {
            if (direction.front().d == 'L') // 왼쪽
                head_dir = turnLeft(head_dir);
            else // 오른쪽
                head_dir = turnRight(head_dir);
            joint.push({head.y, head.x, head_dir});

            direction.pop();
        }
        // 꼬리가 뱀의 꺾인 부분에 도달하면 -> 꼬리 방향 전환
        if (!joint.empty() && tail.y == joint.front().y && tail.x == joint.front().x)
        {
            tail_dir = joint.front().d;
            joint.pop();
        }
    }
    cout << t << '\n';
}

int main()
{
    input();
    solve();

    return 0;
}