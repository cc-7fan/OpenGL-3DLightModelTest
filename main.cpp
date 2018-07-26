#include<GL/glut.h>
#include<stdio.h>

//ϵͳ��Ļ��С��ʼ��
GLint SCREEN_WIDTH = 0;
GLint SCREEN_HEIGHT = 0;
//���ڴ�С��ʼ��
GLint window_width = 1024;
GLint window_height = 768;
//�����������
#define MIDWIDTH window_width/2
#define MIDHEIGHT window_height/2
//����ģ����ת�Ƕ�
GLfloat xAngle = 0.0f;
GLfloat yAngle = 0.0f;
//����ģ�ͳ�ʼ����
GLfloat distancex;
GLfloat distancey;
//��֧�ֵĵ��С��Χ    
GLfloat sizes[2];
//��֧�ֵĵ��С����    
GLfloat step;

//Ĭ�ϳ��ֵ�ģ���ǲ��
GLint flag = 3;

//�߿�|ʵ�壺״̬Ĭ��Ϊ  �߿�
GLint lsr = 0;

GLboolean mouseLeftDown = false;		//����������״̬��Ĭ����δ����

//�Զ���ת״̬
GLboolean RotateStatus = true;

//��ǰ���λ��
GLint mousex;
GLint mousey;

//���ű���
GLfloat times = 1.0f;		//Ĭ�ϱ���Ϊ1.0��

//Ĭ�����ù���
GLboolean lightEnable = true;

//�����Դ����ɫ��λ��
GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };			//������
GLfloat position[] = {10.0f, 3.0f, 2.0f, 0.0f };		//��Դλ��
GLfloat matEmission[] = { 1.0f, 1.0f, 1.0f, 1.0};		//�������ɫ
GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };			    //�����
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };       //���淴��

GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };   // ������ɫ
GLfloat mat_diffuse[] = { 0.2f, 0.5f, 0.8f, 1.0f };   // ɢ����ɫ
GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // ���淴����ɫ
GLfloat high_shininess[] = { 100.0f };                // ���淴��ָ��Ϊ100.0
GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };        // �޲�����ɫ

void init() {			//��Դ�����ʡ���ʵ�г�ʼ��

	//ѡ�����ģ��
	GLfloat local_view[] = { 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	//���û�����
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//���������
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);		//���ò��Ϸ���ָ���������䣩->ȷ��������ɫ
	//���ù�Դλ��
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, local_view);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);  // ����ģ�����巢���Ч�������ⲻ�ǹ�Դ
	//��OpenGL�У�������ȷָ�������Ƿ���Ч����Ч�����������Ч����ֻ�Ǽ򵥵ؽ���ǰ��ɫӳ�䵽��ǰ������ȥ

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);

	glEnable(GL_DEPTH_TEST);		//��Ȳ���
	//��������
	if (lightEnable) {
		glEnable(GL_LIGHTING);
		//����ָ����Դ
		glEnable(GL_LIGHT0);
	}else
		glDisable(GL_LIGHTING);

}

void translate()			//λ����ת����->����廷
{
	glColor3f(0.0f, 1.0f, 1.0f);
	glScalef(times, times, times);
	glTranslatef(distancex, distancey, 0);
	//����ϵ��x����תxAngle��
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	//����ϵ��y����תyAngle��  
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
}

void drawfiveCircle()				//�����廷����ɫ
{
	glPushMatrix();
	glTranslatef(-6.0f, 4.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	if (!lsr)
	{
		glPushMatrix();
		mat_ambient[0] = 0.0f; mat_ambient[1] = 0.0f; mat_ambient[2] = 1.0f;
		mat_diffuse[0] = 0.0; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 1.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutWireTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		mat_ambient[0] = 0.0f; mat_ambient[1] = 0.0f; mat_ambient[2] = 1.0f;
		mat_diffuse[0] = 0.0; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 1.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutSolidTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
		glutSolidTorus(0.5f, 3.0f, 20, 20);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4.5f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	if (!lsr)
	{
		glPushMatrix();
		mat_ambient[0] = 0.0f; mat_ambient[1] = 0.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 0.0; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutWireTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();

	}
	else
	{
		glPushMatrix();
		mat_ambient[0] = 0.0f; mat_ambient[1] = 0.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 0.0; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutSolidTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6.0f, 4.5f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	if (!lsr)
	{
		glPushMatrix();
		mat_ambient[0] = 1.0f; mat_ambient[1] = 0.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 1.0; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutWireTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		mat_ambient[0] = 1.0f; mat_ambient[1] = 0.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 1.0; mat_diffuse[1] = 0.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutSolidTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 0.0f);
	if (!lsr)
	{
		glPushMatrix();
		mat_ambient[0] = 1.0f; mat_ambient[1] = 1.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 1.0; mat_diffuse[1] = 1.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutWireTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		mat_ambient[0] = 1.0f; mat_ambient[1] = 1.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 1.0; mat_diffuse[1] = 1.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutSolidTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	if (!lsr)
	{
		glPushMatrix();
		mat_ambient[0] = 0.0f; mat_ambient[1] = 1.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 0.0; mat_diffuse[1] = 1.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutWireTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		mat_ambient[0] = 0.0f; mat_ambient[1] = 1.0f; mat_ambient[2] = 0.0f;
		mat_diffuse[0] = 0.0; mat_diffuse[1] = 1.0f; mat_diffuse[2] = 0.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glLightfv(GL_LIGHT0, GL_SPECULAR, mat_specular);
		glutSolidTorus(0.5f, 3.0f, 20, 20);
		glPopMatrix();
	}
	glPopMatrix();

}

void display()			//��ͼ����
{
	init();
	//��ʼ�����ڱ�����ɫ
	glClearColor(0.8f, 0.8f, 0.8f, 0.75f);
	//��ģ�建����ֵȫ������Ϊ1    
	glClearStencil(1);
	//����ʹ��ģ����Բ��Ҹ���ģ�滺��    
	glEnable(GL_STENCIL_TEST);
	//��������������Ϊ��ǰ������ɫ����ɫ�������Ȼ�������ģ�建����    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glPushMatrix()��glPopMatrix()�����ʹ�ÿ���������һ�εı任�Ա��α任��Ӱ�졣
	//ʹ���α任������������ϵ��ԭ��Ϊ�ο������
	glPushMatrix();
	
	//����ƽ������    
	glEnable(GL_POINT_SMOOTH);		//�� ��������ʹƽ��
	glHint(GL_POINT_SMOOTH, GL_NICEST);		//ָʾƽ���̶�Ϊ�������
	glEnable(GL_LINE_SMOOTH);			//�߷�����
	glHint(GL_LINE_SMOOTH, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);			//����η�����
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);

	//���������ᣨ��ɫ��    
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	//x��
	glVertex3f(-12.0f, 0.0f, 0.0f);
	glVertex3f(12.0f, 0.0f, 0.0f);
	//y��
	glVertex3f(0.0f, -12.0f, 0.0f);
	glVertex3f(0.0f, 12.0f, 0.0f);
	//z��
	glVertex3f(0.0f, 0.0f, -12.0f);
	glVertex3f(0.0f, 0.0f, 12.0f);
	glEnd();

	//��ͷ
	glPushMatrix();
	glTranslatef(12.0f, 0.0f, 0.0f);			//��ÿ�����������ƽ�Ʋ�����ʹ�����Ϊ��0��0��
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);		//��y����ת90��
	glutSolidCone(0.3, 0.6, 10, 10);		//�ڶϵ�����Բ׶��ͷ
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 12.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 12.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCone(0.3, 0.6, 10, 10);
	glPopMatrix();

	
	switch (flag) {
		//��������   
	case 1:
		//glPushMatrix();
		translate();
		glScalef(8*times, 8*times, 8*times);
		if (lsr == 0) {
			glutWireTetrahedron();
		}
		else if(lsr == 1) {
			glutSolidTetrahedron();
		}
		//glPushMatrix();
		break;
		//��������   
	case 2:
		translate();
		glScalef(8 * times, 8 * times, 8 * times);
		if (lsr == 0) {
			glutWireOctahedron();
		}
		else if(lsr == 1) {
			glutSolidOctahedron();
		}
		break;
		 //����
	case 3:
		translate();
		if (lsr == 0) {
			glutWireSphere(8.0f, 20, 20);
		}
		else if(lsr == 1) {
			glutSolidSphere(8.0f, 20, 20);
		}
		break;
		//���  
	case 4:
		translate();
		if (lsr == 0) {
			glutWireTeapot(6.5f);
		}
		else if(lsr == 1) {
			glutSolidTeapot(6.5f);
		}
		break;
		//Բ׶   
	case 5:
		translate();
		glScalef(2 * times, 2 * times, 2* times);
		if (lsr == 0) {
			glutWireCone(4.0f, 5.0f, 20, 20);
		}
		else if(lsr == 1){
			glutSolidCone(4.0f, 8.0f, 20, 20);
		}
		break;
		//�����廷    
	case 6:
		translate();
		if (lsr == 0) {
			drawfiveCircle();
		}
		else if(lsr == 1){
			drawfiveCircle();
		}
		break;
	default:
		break;
	}
	//�ָ�ѹ��ջ��Matrix    
	glPopMatrix();
	//����������������ָ��    
	glutSwapBuffers();
}

void setupRederingState(void) {				//��Ⱦ��ʼ��
	//����������ɫΪ��ɫ    
	glClearColor(0.0f, 0.0, 0.0, 1.0f);
	//���û滭��ɫΪ��ɫ    
	glColor3f(1.0f, 1.0f, 1.0f);
	//ʹ����Ȳ���    
	glEnable(GL_DEPTH_TEST);
}

void changeSize(GLint width, GLint height)			//���ڸı�ߴ�ʱ����
{
	//������    
	GLfloat ratio;
	//��������ϵΪx(-100.0f,100.0f)��y(-100.0f,100.0f)��z(-100.0f,100.0f)    
	GLfloat coordinatesize = 16.0f;
	//���ڿ��Ϊ��ֱ�ӷ���    
	if ((width == 0) || (height == 0))
		return;
	//�����ӿںʹ��ڴ�Сһ��    
	glViewport(0, 0, width, height);
	//��ͶӰ����Ӧ�����ľ������    
	glMatrixMode(GL_PROJECTION);
	//���õ�ǰָ���ľ���Ϊ��λ����    
	glLoadIdentity();
	ratio = (GLfloat)width / (GLfloat)height;
	//����ͶӰ    
	if (width<height)
		glOrtho(-coordinatesize, coordinatesize, -coordinatesize / ratio, coordinatesize / ratio, -coordinatesize, coordinatesize);
	else
		glOrtho(-coordinatesize*ratio, coordinatesize*ratio, -coordinatesize, coordinatesize, -coordinatesize, coordinatesize);
	//��ģ����ͼ�����ջӦ�����ľ������    
	glMatrixMode(GL_MODELVIEW);
	//���õ�ǰָ���ľ���Ϊ��λ����    
	glLoadIdentity();
}

void menuFunc( int key)		//�˵��ص�����
{
	switch (key) {
	case 1:
		flag = 1;
		break;
	case 2:
		flag = 2;
		break;
	case 3:
		flag = 3;
		break;
	case 4:
		flag = 4;
		break;
	case 5:
		flag = 5;
		break;
	case 6:
		flag = 6;
		break;
	case 7:
		lsr = 0;
		break;
	case 8:
		lsr = 1;
		break;
	case 11:
		ambient[0] = 1.0f; ambient[1] = 0.0f; ambient[2] = 0.0f;
		break;
	case 12:
		ambient[0] = 1.0f; ambient[1] = 0.0f; ambient[2] = 1.0f;
		break;
	case 13:
		ambient[0] = 0.0f; ambient[1] = 1.0f; ambient[2] = 0.0f;
		break;
	case 14:
		ambient[0] = 0.0f; ambient[1] = 0.0f; ambient[2] = 1.0f;
		break;
	case 15:
		ambient[0] = 1.0f; ambient[1] = 1.0f; ambient[2] = 1.0f;
		break;
	case 16:
		ambient[0] = 0.0f; ambient[1] = 0.0f; ambient[2] = 0.0f;
		break;
	case 17:
		lightEnable = true;
		break;
	case 18:
		lightEnable = false;
		break;
	case 19:
		position[0] -= 10.0;
		break;
	case 20:
		position[0] += 10.0;
		break;
	case 21:
		position[2] += 10.0;
		break;
	case 22:
		position[2] -= 10.0; 
		break;
	}
	glutPostRedisplay();
}

void setMenu()			//���ò˵�
{
	
	int slrMenu;
	int modelMenu;
	int mainMenu;
	int colorMenu;
	int lightMenu;
	int lightPositionMenu;

	modelMenu = glutCreateMenu(menuFunc);
	glutAddMenuEntry("��������", 1);
	glutAddMenuEntry("��������", 2);
	glutAddMenuEntry("����", 3);
	glutAddMenuEntry("���", 4);
	glutAddMenuEntry("����Բ׶����", 5);
	glutAddMenuEntry("�����廷",6);

	slrMenu = glutCreateMenu(menuFunc);
	glutAddMenuEntry("�߿�", 7);
	glutAddMenuEntry("ʵ��", 8);

	colorMenu = glutCreateMenu(menuFunc);
	glutAddMenuEntry("��ɫ", 11);
	glutAddMenuEntry("Ʒ��ɫ", 12);
	glutAddMenuEntry("��ɫ", 13);
	glutAddMenuEntry("��ɫ", 14);
	glutAddMenuEntry("��ɫ", 15);
	glutAddMenuEntry("��ɫ", 16);

	lightMenu = glutCreateMenu(menuFunc);
	glutAddMenuEntry("����", 17);
	glutAddMenuEntry("�ر�", 18);

	lightPositionMenu = glutCreateMenu(menuFunc);
	glutAddMenuEntry("��Դ�����ƶ�", 19);
	glutAddMenuEntry("��Դ�����ƶ�", 20);
	glutAddMenuEntry("��Դ�����ƶ�", 21);
	glutAddMenuEntry("��Դ�����ƶ�", 22);

	mainMenu = glutCreateMenu(menuFunc);
	glutAddSubMenu("ģ��", modelMenu);
	glutAddSubMenu("�߿�|ʵ��", slrMenu);
	glutAddSubMenu("��������ɫѡ��", colorMenu);
	glutAddSubMenu("���ù���", lightMenu);
	glutAddSubMenu("����λ��",lightPositionMenu);


	//���˵����ӵ�����Ҽ���    
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void keyFunc(int key,int x,int y)			//���̿���
{
	//��ת
	if (key == GLUT_KEY_UP)
		xAngle -= 5.0f;			//��x��˳ʱ��ת
	else if (key == GLUT_KEY_DOWN)
		xAngle += 5.0f;			//��x����ʱ��ת
	else if (key == GLUT_KEY_LEFT)
		yAngle -= 5.0f;			//��y��˳ʱ��ת
	else if (key == GLUT_KEY_RIGHT)
		yAngle += 5.0f;			//��y����ʱ��ת
	
	//����
	if (key == GLUT_KEY_F7)
	{
		times += 0.2f;
		glutPostRedisplay();
	}
	else if (key == GLUT_KEY_F8)
	{
		times -= 0.2f;
		glutPostRedisplay();
	}
	
	//��ɫ�仯
	GLfloat r = 0.05f; GLfloat g = 0.05f; GLfloat b = 0.05f;
	switch(key)
	{
		case GLUT_KEY_F1:
			ambient[0] += r;
			if (ambient[0] == 1.0f || ambient[1] == 1.0f || ambient[2] == 1.0f)
				break;
			
		case GLUT_KEY_F2:
			ambient[1] += g;
			break;
		case GLUT_KEY_F3:
			ambient[2] += b;
				break;
		case GLUT_KEY_F4:
			ambient[0] -= r;
				break;
		case GLUT_KEY_F5:
			ambient[1] -= g;
				break;
		case GLUT_KEY_F6:
			ambient[2] -= b;
				break;
		case GLUT_KEY_F9:
			position[2] += 8.0;
			break;
		case GLUT_KEY_F10:
			position[2] -= 8.0;
			break;
		case GLUT_KEY_F11:
			position[0] -= 8.0; position[1] -= 8.0;
			break;
		case GLUT_KEY_F12:
			position[0] += 8.0; position[1] += 8.0;
			break;
		default:
			break;
	
	}

	glutPostRedisplay();
}

void mouseFunc( int key,int state, int x, int y)			//������¼�
{

	if (key == 0)
		if (state == 0)
			mouseLeftDown = true;
		else if (state == GLUT_UP)
			mouseLeftDown = false;

	//��������
	if (mouseLeftDown == false && key == GLUT_WHEEL_UP)
	{
		times += 0.2f;
		glutPostRedisplay();
	}
	else if (mouseLeftDown == false && key == GLUT_WHEEL_DOWN)
	{
		times -= 0.2f;
		glutPostRedisplay();
	}
	
}

void mouseMove(int x, int y)			//����϶�������Ӧλ�ý�����ת
{
	mousex = x;
	mousey = y;

		if ((x > 0 && x<MIDWIDTH / 2) && (y>MIDHEIGHT / 2 && y < MIDHEIGHT * 3 / 2))
			yAngle -= 1.0f;			//����ת
		if ((x<window_width && x>MIDWIDTH * 3 / 2) && (y > MIDHEIGHT / 2 && y < MIDHEIGHT * 3 / 2))
			yAngle += 1.0f;			//����ת
		if ((y > 0 && y<MIDHEIGHT / 2) && (x>MIDWIDTH / 2 && x < MIDWIDTH * 3 / 2))
			xAngle -= 1.0f;			//����ת
		if ((x > MIDWIDTH / 2 && x < MIDWIDTH * 3 / 2) && (y<window_height && y > MIDHEIGHT * 3 / 2))
			xAngle += 1.0f;			//����ת

	glutPostRedisplay();
}

void OnTimer(void)			//����ʱ  �����Զ���ת
{
	yAngle += 0.075f;
	if (yAngle >= 360)
	{
		xAngle += 0.075f;
		yAngle = 0;
	}
	if (xAngle >= 360)
	{
		yAngle += 0.075f;
		xAngle = 0;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	//���ϵͳ��ʼ������
	glutInit(&argc, argv);
	//���ó�ʼ��ʾģʽ��ʹ�� ˫������ ��RGBA��ɫģʽ�� ����� �� ģ�建���� 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//������Ļ��СΪϵͳ��ȡ�Ŀ�Ⱥ͸߶�
	SCREEN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
	SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
	//���ô�������
	glutCreateWindow("OpenGL-3D");
	//���ô��ڵĴ�С
	glutReshapeWindow(window_width, window_height);
	//���ô���λ��->������ʾ
	glutPositionWindow((SCREEN_WIDTH - window_width) / 2, (SCREEN_HEIGHT - window_height) / 2);
	//���ò˵�����
	setMenu();
	//���ô��ڴ�С�ı��ִ�еĺ���
	glutReshapeFunc(changeSize);
	//��ʾ�ص�����
	glutDisplayFunc(display);
	//������
	glutSpecialFunc(keyFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(mouseMove);
	//������Ⱦ����
	setupRederingState();
	//��ʱ��(���лص�����)
	glutIdleFunc(&OnTimer);
	//������ѭ��
	glutMainLoop();

}