#include <iostream>
#include <stdlib.h> //Needed for "exit" function
#include "math.h"
#include<GL/glut.h>
#include<unistd.h>
#include<string.h>
#define sign(x) ((x>0)?1:((x<0)?-1:0))
int flag = 0,flag1=1, k = 0,flag2=2;
//Include OpenGL header files, so that we can use OpenGL

void *currentfont;

typedef struct node {
	char name[20]; // name of the node
	float data;
	struct node* right;
	struct node* left;
	struct node* parent;
	struct node* next;
}NODE;

NODE* root = NULL;

using namespace std;

void display_list(NODE* head) {
	if (head) {
		cout << "\nList contents:\n";
		NODE* temp = head;
		while (temp) {
			cout << "Node : " << temp->name << "  frequency:" << temp->data << endl;
			temp = temp->next;
		}
	}
	else {
		cout << "\nEmpty List";
	}
}


void find_smallest(NODE* head, NODE** smallest1, NODE** smallest2) {
	*smallest1 = NULL;
	*smallest2 = NULL;
	NODE* t = head;
	while (t) {
		// Skip the nodes who has parent 
		if (t->parent) {
			t = t->next;
			continue;
		}

		if (!*smallest1) {
			*smallest1 = t;
		}
		else if (!*smallest2) {
			*smallest2 = t;
		}
		else if (t->data < (*smallest1)->data) {
			if ((*smallest1)->data < (*smallest2)->data) {
				*smallest2 = *smallest1;
			}
			*smallest1 = t;
		}
		else if (t->data < (*smallest2)->data) {
			*smallest2 = t;
		}
		else {
			// Do nothing
		}

		if (*smallest1 && *smallest2) {
			if ((*smallest1)->data >(*smallest2)->data) {
				NODE* temp = *smallest1;
				*smallest1 = *smallest2;
				*smallest2 = temp;
			}
		}
		t = t->next;
	}
}

void add_element(NODE** head, NODE** e) {
	if (!*head) {
		*head = *e;
	}
	else {
		NODE* t = *head;
		while (t->next != NULL) {
			t = t->next;
		}
		t->next = *e;
	}
}

void tree_traversal(NODE* root, char code[20]) {
	if (!root) {
		return;
	}
	//cout<<"\n NODE : "<<root->name<<"  prob: "<<root->data;
	if (root->left == NULL && root->right == NULL) {
		cout << " \nNODE : " << root->name << "  Freq : " << root->data << "  code: " << code;
		return;
	}
	int len = strlen(code);
	if (root->left) {
		code[len] = '0';
		code[len + 1] = '\0';
		tree_traversal(root->left, code);
	}
	if (root->right) {
		code[len] = '1';
		code[len + 1] = '\0';
		tree_traversal(root->right, code);
	}
}

void drawCircle(float radius, float x1, float y1)
{
	//filled circle
	float x2, y2;
	float angle;


	glColor3f(0.8, 0.498039, 0.196078);
	glBegin(GL_POLYGON);
	//glVertex2f(x1, y1);

	for (angle = 1.0f;angle<361.0f;angle += 0.2)
	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glFlush();
	glEnd();

}

void draw_line1(float x1, float y1, float x2, float y2) {

	glColor3f(0.0, 0.6, 0.6);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void draw_text(char* text,float x, float y) {
     GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
     glRasterPos3f(x, y, 0);
     for (int i = 0; text[i] != '\0'; i++){
         glutBitmapCharacter(font_style, text[i]);
     }
}
/*void draw_text1(char* text,float x, float y) {
     FTGLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
     glRasterPos3f(x, y, 0);
     for (int i = 0; text[i] != '\0'; i++){
         glutBitmapString(font_style, text[i]);
     }
}*/

void drawNode1(NODE* t_root, float x1, float y1, int level) {
	if (t_root == NULL) {
		return;
	}

	float segments = 25;
	float radius = 1.0;
	float left_angle = 245;
	float right_angle = 115;
	float branch_length = 12 - level * 2.5;
	float angle_change = 20;
	// Draw the current circle

	drawCircle(radius, x1, y1);
	//glColor3f(1.0, 1.0, 0.0);
	//draw_text(t_root->name, x1, y1 + 1);

	if (t_root->left) {
		// Draw the Left circle
		float angle1 = left_angle - level * angle_change;
		double radian2 = angle1 * 3.14 / 180;
		float m = (double)tan((double)radian2);
		float x2 = x1 + branch_length * sin((double)radian2);
		float y2 = y1 + branch_length * cos((double)radian2);

		drawNode1(t_root->left, x2, y2, level + 1);

		//draw_line1(x1, y1, x2, y2);

		float x3 = (x1 + x2) / 2;
		float y3 = (y1 + y2) / 2;
		char label1[2];
		label1[0] = '0';
		label1[1] = '\0';

		//glColor3f(1.0, 1.0, 0.0);
		//draw_text(label1, x3, y3 + 1);
	}

	if (t_root->right) {
		// Draw the Right circle
		float angle2 = right_angle + level * angle_change;
		float radian2 = angle2 * 3.14 / 180;
		float m = (double)tan((double)radian2);
		float x4 = x1 + branch_length * sin((double)radian2);
		float y4 = y1 + branch_length * cos((double)radian2);
		drawNode1(t_root->right, x4, y4, level + 1);
		//draw_line1(x1, y1, x4, y4);

		float x5 = (x1 + x4) / 2;
		float y5 = (y1 + y4) / 2;
		char label2[2];
		label2[0] = '1';
		label2[1] = '\0';
		//glColor3f(1.0, 1.0, 0.0);
		//draw_text(label2, x5, y5 + 1);

	}
	glFlush();

}
void drawNode2(NODE* t_root, float x1, float y1, int level) {
	if (t_root == NULL) {
		return;
	}

	float segments = 25;
	float radius = 1.0;
	float left_angle = 245;
	float right_angle = 115;
	float branch_length = 12 - level * 2.5;
	float angle_change = 20;
	// Draw the current circle

	drawCircle(radius, x1, y1);
	//glColor3f(1.0, 1.0, 0.0);
	//draw_text(t_root->name, x1, y1 + 1);

	if (t_root->left) {
		// Draw the Left circle
		float angle1 = left_angle - level * angle_change;
		double radian1 = angle1 * 3.14 / 180;
		float m = (double)tan((double)radian1);
		float x2 = x1 + branch_length * sin((double)radian1);
		float y2 = y1 + branch_length * cos((double)radian1);

		drawNode2(t_root->left, x2, y2, level + 1);
		draw_line1(x1, y1, x2, y2);

		float x3 = (x1 + x2) / 2;
		float y3 = (y1 + y2) / 2;
		char label1[2];
		label1[0] = '0';
		label1[1] = '\0';
		//glColor3f(1.0, 1.0, 0.0);
		//draw_text(label, x3, y3 + 1);
	}

	if (t_root->right) {
		// Draw the Right circle
		float angle2 = right_angle + level * angle_change;
		float radian2 = angle2 * 3.14 / 180;
		float m = (double)tan((double)radian2);
		float x4 = x1 + branch_length * sin((double)radian2);
		float y4 = y1 + branch_length * cos((double)radian2);
		drawNode2(t_root->right, x4, y4, level + 1);
		draw_line1(x1, y1, x4, y4);

		float x5 = (x1 + x4) / 2;
		float y5 = (y1 + y4) / 2;
		char label2[2];
		label2[0] = '1';
		label2[1] = '\0';
		//glColor3f(1.0, 1.0, 0.0);
		//draw_text(label, x3, y3 + 1);

	}
	glFlush();
}
void drawNode3(NODE* t_root, float x1, float y1, int level) {
	if (t_root == NULL) {
		return;
	}

	float segments = 25;
	float radius = 1.0;
	float left_angle = 245;
	float right_angle = 115;
	float branch_length = 12 - level * 2.5;
	float angle_change = 20;
	// Draw the current circle

	drawCircle(radius, x1, y1);
	//glColor3f(1.0, 1.0, 0.0);
	glColor3f(0.737255, 0.560784, 0.560784);
	draw_text(t_root->name, x1, y1 + 1);

	if (t_root->left) {
		// Draw the Left circle
		float angle1 = left_angle - level * angle_change;
		double radian1 = angle1 * 3.14 / 180;
		float m = (double)tan((double)radian1);
		float x2 = x1 + branch_length * sin((double)radian1);
		float y2 = y1 + branch_length * cos((double)radian1);

		drawNode3(t_root->left, x2, y2, level + 1);
		draw_line1(x1, y1, x2, y2);

		float x3 = (x1 + x2) / 2;
		float y3 = (y1 + y2) / 2;
		char label1[2];
		label1[0] = '0';
		label1[1] = '\0';
		//glColor3f(1.0, 1.0, 0.0);
		//draw_text(label1, x3, y3 + 1);
	}

	if (t_root->right) {
		// Draw the Right circle
		float angle2 = right_angle + level * angle_change;
		float radian2 = angle2 * 3.14 / 180;
		float m = (double)tan((double)radian2);
		float x4 = x1 + branch_length * sin((double)radian2);
		float y4 = y1 + branch_length * cos((double)radian2);
		drawNode3(t_root->right, x4, y4, level + 1);
		draw_line1(x1, y1, x4, y4);

		float x5 = (x1 + x4) / 2;
		float y5 = (y1 + y4) / 2;
		char label2[2];
		label2[0] = '1';
		label2[1] = '\0';
		//glColor3f(1.0, 1.0, 0.0);
		//draw_text(label2, x5, y5 + 1);

	}

	glFlush();
}
void drawNode4(NODE* t_root, float x1, float y1, int level) {
	if (t_root == NULL) {
		return;
	}

	float segments = 25;
	float radius = 1.0;
	float left_angle = 245;
	float right_angle = 115;
	float branch_length = 12 - level * 2.5;
	float angle_change = 20;
	// Draw the current circle

	drawCircle(radius, x1, y1);
	//glColor3f(1.0, 1.0, 0.0);
	glColor3f(0.737255, 0.560784, 0.560784);
	draw_text(t_root->name, x1, y1 + 1);

	if (t_root->left) {
		// Draw the Left circle
		float angle1 = left_angle - level * angle_change;
		double radian1 = angle1 * 3.14 / 180;
		float m = (double)tan((double)radian1);
		float x2 = x1 + branch_length * sin((double)radian1);
		float y2 = y1 + branch_length * cos((double)radian1);

		drawNode4(t_root->left, x2, y2, level + 1);
		draw_line1(x1, y1, x2, y2);

		float x3 = (x1 + x2) / 2;
		float y3 = (y1 + y2) / 2;
		char label1[2];
		label1[0] = '0';
		label1[1] = '\0';
		glColor3f(1.0, 1.0, 0.0);
		draw_text(label1, x3, y3 + 1);
	}

	if (t_root->right) {
		// Draw the Right circle
		float angle2 = right_angle + level * angle_change;
		float radian2 = angle2 * 3.14 / 180;
		float m = (double)tan((double)radian2);
		float x4 = x1 + branch_length * sin((double)radian2);
		float y4 = y1 + branch_length * cos((double)radian2);
		drawNode4(t_root->right, x4, y4, level + 1);
		draw_line1(x1, y1, x4, y4);

		float x5 = (x1 + x4) / 2;
		float y5 = (y1 + y4) / 2;
		char label2[2];
		label2[0] = '1';
		label2[1] = '\0';
		glColor3f(1.0, 1.0, 0.0);
		draw_text(label2, x5, y5 + 1);

	}

	glFlush();
}

void setFont(void *font)
{
	currentfont = font;
}
void frontscreen()
{
	char a[100], b[100], c[100], d[100], e[100], f[332], g[100], h[100],i[100],j[100],k[100];
	strcpy(a, "MANGALORE INSTITUTE OF TECHNOLOGY AND ENGINEERING");
	strcpy(b, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	strcpy(c, "A MINI PROJECT ON");
	strcpy(d, "\"HUFFMAN ENCODING\"");
	strcpy(e, "BY");
	strcpy(f, "SHOBHITH NAYAK                4MT16CS091");
	strcpy(g, "       SHREYAN                           4MT16CS096");
        strcpy(i, "GUIDES");
        strcpy(j, "PRASHANTH B S");
        strcpy(k, "SARANYA BABU");

	strcpy(h, "PRESS ENTER TO START");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 10, -30);
	glColor3f(1, 1, 1);
	glColor3f(0, 0, 1);
	draw_text(a, -16, 5);
	glColor3f(0.7, 0, 1);
	draw_text(b, -15, 1);
	glColor3f(1, 0.5, 0);
	draw_text(c, -5, -3);
	glColor3f(1, 0, 0);
	draw_text(d, -6, -5);
	glColor3f(1, 0.5, 0);
	draw_text(e, -1, -10);
	glColor3f(0.5, 0, 0.5);
	draw_text(f, -12, -12);
        glColor3f(0.5,0,0.5);
	draw_text(g, -12, -14);
        glColor3f(1, 0.5, 0);
        draw_text(i, -2, -18);
        glColor3f(0, 0.5, 0.5);
	draw_text(j, -4, -20);
        draw_text(k, -4, -22);
	glColor3f(1, 0.1, 1);
	draw_text(h, -6, -26);
	glFlush();
/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0, 0, 1);
	drawstring(47.0 - 108.0, 140.0, 0.0, "MANGALORE INSTITUTE OF TECHNOLOGY AND ENGINEERING");
	glColor3f(0.7, 0.0, 1);
	drawstring(50.0 - 108.0, 128.0, 0.0, "DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	glColor3f(1, 0.5, 0);
	drawstring(60.0 - 80.0, 106.0, 0.0, "A MINI PROJECT ON");
	glColor3f(1, 0, 0);
	drawstring(62 - 80, 96, 0.0, "\"Huffman Encoding\"");
	glColor3f(1, 0.5, 0);
	drawstring(78 - 80, 76, 0.0, "BY");
	glColor3f(0.5, 0, 0.5);
	drawstring(25 - 60, 66, 0.0, "Shobhith Nayak             4MT16CS091");
        glColor3f(0.5, 0, 0.5);
	drawstring(25 - 60, 56, 0.0, "Shreyan                          4MT16CS096");
	glColor3f(1, 0.5, 0);
	drawstring(40 - 50, 36, 0.0, "GUIDES");
	glColor3f(0.5, 0, 0.5);
	drawstring(43 - 60, 26, 0.0, "Mr.Prashanth BS");
        glColor3f(0.5, 0, 0.5);
	drawstring(43 - 60, 16, 0.0, "Ms.Saranya Babu");
	glColor3f(1, 0.1, 1);
	drawstring(22 - 50,1, 0.0, "PRESS ENTER TO START");
	glutSwapBuffers();
	glFlush();*/
}
void description()
{
	char a[200], b[100], c[100], d[100], e[100], f[332], g[100], h[100],i[100],k[100],l[100],m[100],j[100];
        strcpy(k,"DESCRIPTION");
	strcpy(a, "The huffman code is a particular type of optimal prefix");
          strcpy(l,"code that is commanly used for lossless data compression.");
	strcpy(b, "Here we are using"); 
strcpy(m,"1.   key 1 to display the nodes of the tree");
	strcpy(d, "2.   Key 2 to give the link between the two nodes");
	strcpy(e, "3.   Key 3 to display the name of the each node");
	strcpy(f, "4.   Key 4 to display the code bit for each of the link");
	strcpy(g, "       a.  bit \'0\' for left side links");
        strcpy(i, "       b.  bit \'1\' for right side links");
        strcpy(j, "5.   Key 6 to overall demonstration of the process");
        strcpy(h, "PRESS SPACE BAR TO START");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 10, -30);
	glColor3f(1, 1, 1);
        glColor3f(0, 0, 1);
        draw_text(k,-4,6);
         
        usleep(12000);
        glColor3f(0.2, 0.5, 1);
        draw_text(a, -13, 2);
	glColor3f(0.2, 0.5, 1);
        draw_text(l,-13,0);
        
         usleep(1000000);
glFlush();
	glColor3f(1, 0, 1);
	draw_text(b, -5, -4);
        glColor3f(1, 0, 0);
	draw_text(m, -11, -6);
	glColor3f(1, 0, 0);
	draw_text(d, -11, -8);
	glColor3f(1, 0, 0);
	draw_text(e, -11, -10);
       
        usleep(2000000);
	glColor3f(1, 0, 0);
        draw_text(f, -11, -12);
        glColor3f(1,0,0);
	draw_text(g, -10, -14);
        glColor3f(1, 0, 0);
        draw_text(i, -10, -16);
        glColor3f(1, 0, 0);
	draw_text(j, -11, -18);
        glColor3f(1, 1, 0);
        draw_text(h, -8, -24);
	glFlush();
}
void decide()
{
	if (k == 1)
		drawNode1(root, 0, 0, 0);
	if (k == 2)
		drawNode2(root, 0, 0, 0);
	if (k == 3)
		drawNode3(root, 0, 0, 0);
	if (k == 4)
		drawNode4(root, 0, 0, 0);
        if(k==5)
                glFlush();
                //drawNode1(root, 0, 0, 0);
               
}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 10, -30);
	//glColor3f(1, 1, 1);
	decide();
	glFlush();
	//glutSwapBuffers();
	//glutPostRedisplay();
}
void last()
{
char a[100],b[100],c[100],d[100],e[100],f[100],g[100],h[100],i[100];
strcpy(a, "The huffman code is a");
strcpy(b,"a particular type of");
strcpy(c,"optimal prefix code");
strcpy(d,"that is mainly used");
strcpy(e,"    for lossless ");
strcpy(f,"data compression!");
strcpy(g, "This is the optimal");
strcpy(h,"tree for the huffman ");
strcpy(i,"      coding!");
//strcpy(j,"that is mainly used");
//strcpy(k,"    for lossless ");
//strcpy(l,"data compression");
        
	//glColor3f(0.7, 0, 1);
//glColor3f(0.7, 0, 1);
       glColor3f(1,0,0.5);
        draw_text(a, -25, 0);
	glColor3f(1,0,0.5);
        draw_text(b,-25,-2);
	glColor3f(1,0,0.5);
        draw_text(c,-25,-4);
        glColor3f(1,0,0.5);
        draw_text(d,-25,-6);
        glColor3f(1,0,0.5);
        draw_text(e,-25,-8);
        glColor3f(1,0,0.5);
        draw_text(f,-25,-10);
glColor3f(1,0,0.5);
        draw_text(g,14,0);
        glColor3f(1,0,0.5);
        draw_text(h,14,-2);
        glColor3f(1,0,0.5);
        draw_text(i,14,-4);
usleep(1000000);
drawNode1(root, 0, 0, 0);
usleep(2000000);
drawNode2(root, 0, 0, 0);
usleep(3000000);
drawNode3(root, 0, 0, 0);
usleep(4000000);
drawNode4(root, 0, 0, 0);
usleep(5000000);

glFlush();

}
void mydisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (flag == 0)
		frontscreen();
	if (flag == 1)
             description();
		//display();
        if (flag == 2)
             display();
        if (flag == 3)
             last();
             glFlush();
}


void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 13:if (flag == 0) //Ascii of 'enter' key is 13
		flag = 1;
		break;
        case 32:if(flag==1)
                 flag=2;
                  break;
        case '6':if(flag==2)
                  flag=3;
                  break;
	case 27:exit(0);
		break;
	}

	if (key == '1')
		k = 1;
	if (key == '2')
		k = 2;
	if (key == '3')
		k = 3;
	if (key == '4')
		k = 4;
        if(key=='5')
                k=5;
	fflush(stdin);
	mydisplay();
}

int main(int argc, char** argv)
{


	NODE* list = NULL;
	float arr[10];
	int n;
	cout << "Enter n:";
	cin >> n;
	for (int i = 0; i<n; i++) {
		cin >> arr[i];
		// Create a new node and append it to the list 
		NODE* current = new NODE;
		current->data = arr[i];
		current->next = NULL;
		current->left = NULL;
		current->right = NULL;
		current->parent = NULL;
		current->name[0] = 65 + i; current->name[1] = '\0';

		// Appending the node to the list 
		add_element(&list, &current);
	}

	// Display the nodes entered by the user along with their probabilities 
	display_list(list);


	while (1) {

		// Find the 2 smallest elements from the list 
		NODE* smallest1 = NULL;
		NODE* smallest2 = NULL;
		find_smallest(list, &smallest1, &smallest2);

		if (!smallest2) {
			root = smallest1;
			break;
		}

		float small1 = smallest1->data;
		float small2 = smallest2->data;
		NODE* current = new NODE;
		current->data = small1 + small2;
		current->left = smallest1;
		current->right = smallest2;
		current->parent = NULL;
		current->next = NULL;
		strcpy(current->name, smallest1->name);
		strcat(current->name, smallest2->name);

		smallest1->parent = current;
		smallest2->parent = current;

		add_element(&list, &current);

	}

	cout << "\n\nHuffman code :\n\n";
	char code[20];
	code[0] = '\0';
	tree_traversal(root, code);

	// OPENGL Drawing functions 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Huffman Code");

	// Register function pointers to the drawing framework 
	glutDisplayFunc(mydisplay);
	//glutIdleFunc(mydisplay);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	cout << endl;
	return 0;
}
