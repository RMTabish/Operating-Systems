#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <queue>
#include <condition_variable>
#include <mutex>

using namespace std;

atomic<char> keyInputP1(' ');
atomic<char> keyInputP2(' ');

int n;
string name1;
string name2;

struct Player {
    int id;
    int x;
    int y;
};

struct Item {
    int x;
    int y;
};

void generate_random_num() {
    srand(time(NULL));
    int p = rand() % 99 + 10;
    p *= 1;
    p = 2541 / p;
    p = p % 25;
    if (p < 10) {
        p += 10;
    }
    n = p;
}

Player p1 = {0, 0, 0};
Player p2 = {1, n - 1, n - 1};

Item item = {0, 0};
int score1 = 0;
int score2 = 0;

bool itemExists = false;

class MessageQueue {
public:
    void push(const pair<int, Player>& msg) {
        unique_lock<mutex> lock(m);
        q.push(msg);
        lock.unlock();
    }

    pair<int, Player> pop() {
        unique_lock<mutex> lock(m);
        if (!q.empty()) {
            auto msg = q.front();
            q.pop();
            return msg;
        }
        return make_pair(-1, Player{-1, -1, -1});
    }

    bool empty() {
        unique_lock<mutex> lock(m);
        return q.empty();
    }

private:
    queue<pair<int, Player>> q;
    mutex m;
};

MessageQueue p1Queue;
MessageQueue p2Queue;



void movePlayer(Player &player, char key) {
    int x = player.x;
    int y = player.y;
    if (key == 'w' || key == 'i') {
        if (player.y < n - 2) {
            y++;
        }
    } else if (key == 's' || key == 'k') {
        if (player.y > 1) {
            y--;
        }
    } else if (key == 'a' || key == 'j') {
        if (player.x > 1) {
            x--;
        }
    } else if (key == 'd' || key == 'l') {
        if (player.x < n - 2) {
            x++;
        }
    }

    pair<int, Player> msg = make_pair(player.id, Player{player.id, x, y});
    if (player.id == 0) {
        p1Queue.push(msg);
    } else {
        p2Queue.push(msg);
    }
}

void handleKeypress(unsigned char key, int x, int y) {
    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        keyInputP1.store(key);
    }
}
void handleSpecialKeypress(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        keyInputP2.store('i');
    } else if (key == GLUT_KEY_DOWN) {
        keyInputP2.store('k');
    } else if (key == GLUT_KEY_LEFT) {
        keyInputP2.store('j');
    } else if (key == GLUT_KEY_RIGHT) {
        keyInputP2.store('l');
    }
}


void collectItem(Player &player) {
    if (player.x == item.x && player.y == item.y) {
        itemExists = false;
        srand(time(NULL));
    int x = rand() % (n - 2) + 1;
    int y = rand() % (n - 2) + 1;
    item.x = x;
    item.y = y;
    itemExists = true;
        if (player.id == 0) {
            score1++;
        } else {
            score2++;
        }
    }
}

void updateGameState() {
    while (!p1Queue.empty()) {
        auto msg = p1Queue.pop();
        if (msg.first != -1) {
            p1 = msg.second;
            collectItem(p1);
        }
    }

    while (!p2Queue.empty()) {
        auto msg = p2Queue.pop();
        if (msg.first != -1) {
            p2 = msg.second;
            collectItem(p2);
        }
    }
}

void playerThreadFunc(Player &player, atomic<char> &keyInput) {
    while (true) {
        char key = keyInput.load();
        if (key != ' ') {
            movePlayer(player, key);
            keyInput.store(' ');
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Dplayer(const Player &player, float r, float g, float b) {
    glColor3f(r, g, b);
    glRectf(player.x, player.y, player.x + 1, player.y + 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);


 //drawing the grid
        glColor3f(1.0, 1.0, 1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = 1; i <= n; i++) {
        glVertex2f(i, 1);
        glVertex2f(i, n - 1);
        glVertex2f(1, i);
        glVertex2f(n, i);
    }
    glEnd();

    if (itemExists==true) {
    //drawing the obs
    glColor3f(0.0, 0.0, 1.0);
    glRectf(item.x, item.y, item.x + 1, item.y + 1);

    glColor3f(0.0, 0.0, 1.0);
    glRectf(item.x, item.y, item.x + 1, item.y + 1);
    }

    Dplayer(p1, 1.0, 0.0, 0.0);
    Dplayer(p2, 0.0, 1.0, 0.0);


//displayin gthe scores
        glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(1, n - 0.5);
    string scoreStr = name1+": " + to_string(score1) + " "+name2+": " + to_string(score2);
    for (char i : scoreStr) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, i);
    }

    glutSwapBuffers();
    glutPostRedisplay(); // Call the display function again
}

int main(int argc, char **argv) {
    generate_random_num();

    cout << "Enter the name of first player" << endl;
    cin >> name1;
    cout << "Enter the name of second player" << endl;
    cin >> name2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ma to Thak giya ");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, n, 0.0, n);
    glMatrixMode(GL_MODELVIEW);
    srand(time(NULL));
    int x = rand() % (n - 2) + 1;
    int y = rand() % (n - 2) + 1;
    item.x = x;
    item.y = y;
    itemExists = true;

    glutDisplayFunc(display);
      glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKeypress);
    glutIdleFunc(updateGameState);

thread player1Thread(playerThreadFunc, ref(p1), ref(keyInputP1));
thread player2Thread(playerThreadFunc, ref(p2), ref(keyInputP2));



    player1Thread.detach();
    player2Thread.detach();

    glutMainLoop();

    return 0;
}
