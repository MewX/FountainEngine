#include <fountain/ft_3dmodel.h>
#include <fountain/ft_data.h>
#include <GL/gl.h>
#include <cstdio>
#include <vector>

using ft3DModel::ObjModel;

typedef struct {
	int i[3];
} ftVec3Index;

void ft3DModel::init()
{
}

ObjModel::ObjModel(const char *fileName)
{
	openFile(fileName);
	neverRendered = 1;
}

ObjModel::~ObjModel()
{
	delete vtx;
}

void ObjModel::openFile(const char *fileName)
{
	char tmp;
	int tmpInt;
	std::vector<ftVec3> v;
	std::vector<ftVec3Index> p;
	ftVec3 tmpV;
	ftVec3Index tmpP;
	v.clear();
	p.clear();
	v.push_back(tmpV);
	std::FILE *objFile = std::fopen(fileName, "r");
	vecN = 1;
	indexN = 0;
	if (objFile != NULL) {
		for (;;) {
			while (tmpInt =
			            std::fscanf(objFile, "%c", &tmp), tmpInt != EOF
			        && tmp != '\n') ;
			if (std::fscanf(objFile, "%c", &tmp) == EOF)
				break;
			if (tmp == 'v') {
				for (int i = 0; i < 3; i++) {
					tmpInt =
					    std::fscanf(objFile, "%f",
					                &tmpV.
					                xyz[i]);
					if (tmpInt != 1)
						break;
				}
				v.push_back(tmpV);
				vecN++;
			} else {
				if (tmp == 'f') {
					tmpInt =
					    std::fscanf(objFile, "%d%d%d",
					                &tmpP.i[0],
					                &tmpP.i[1],
					                &tmpP.i[2]);
					if (tmpInt != 3)
						continue;
					p.push_back(tmpP);
					indexN++;
				}
			}
		}
		std::fclose(objFile);
		vtx = new float[indexN * 3][3];
		for (int tri = 0; tri < indexN; tri++) {
			for (int vti = 0; vti < 3; vti++) {
				for (int coori = 0; coori < 3; coori++)
					vtx[tri * 3 + vti][coori] = v[p[tri].i[vti]].xyz[coori];
			}
		}
		neverRendered = 1;
	} else {
		std::printf("Open \"%s\" error!\n", fileName);
	}
}

void ObjModel::render()
{
	//if (neverRendered) {
	//	listIndex = glGenLists(1);
	//	glNewList(listIndex, GL_COMPILE);
	//for (int i = 0; i < indexN; i++) {
	//	glBegin(GL_LINE_LOOP);
	//	glVertex3fv(v[p[i].a].xyz);
	//	glVertex3fv(v[p[i].b].xyz);
	//	glVertex3fv(v[p[i].c].xyz);
	//	glEnd();
	//}
	//	glEndList();
	//	neverRendered = 0;
	//} else {
	//	glCallList(listIndex);
	//}
	glEnable(GL_DEPTH_TEST);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vtx);
	glDrawArrays(GL_TRIANGLES, 0, indexN * 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(2.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vtx);
	glDrawArrays(GL_TRIANGLES, 0, indexN * 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
