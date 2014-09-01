/*
 *
 *   2014
 *   Author:       Giulia Picciau - DIBRIS, Università degli studi di Genova
 *   Supervisors:  Leila De Floriani - DIBRIS, Università degli studi di Genova
 *                 Patricio Simari - Department of Electrical Engineering and Computer Science, The Catholic University of America
 *
 *   Title:          Fast and scalable mesh superfacets
 *   Submission to Pacific Graphics 2014
 *
 *
 **/

#ifndef MESHVISUALIZER_H
#define MESHVISUALIZER_H

#include <QWidget>
#include <QGLWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QString>
#include <QStringList>
#include <cfloat>
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glu.h>
#include "Reader.h"
#include "colormapper.h"
#include "normals.h"
#include "dialogs.h"

//data types used for map structures
typedef unsigned long int faceind;
typedef unsigned long long int edgekey;


/**
 *
 * @brief The MeshVisualizer class opens a window to display the segmentation
 * applied to a mesh (one color per segment)
 */
class MeshVisualizer : public QGLWidget
{
    Q_OBJECT
public:
    explicit MeshVisualizer(QWidget *parent = 0);
    MeshVisualizer(string fname, string sname);
    
    //Data structures to contain the object
    void InitStructures();

    //Position and orientation
    inline void initParams(){
        objPX=0.0;
        objPY=0.0;
        objPZ=0.0;

        objRX=0.0;
        objRY=0.0;
        objRZ=0.0;

        rotationX=0.0;
        rotationY=0.0;
        rotationZ=0.0;
    }

    /// Sets the name of the mesh to be visualized
    inline void setMeshName(string filename){
        this->meshFile=filename;
    }
    /// Sets the name of the segmentation to be appplied to the mesh
    inline void setSegmName(string filename){
        this->segFile=filename;
    }

    /// When we change the segmentation applied to a mesh
    inline void destroyWidget(){
        this->destroy();
    }

    /// to be able to call the paint function from outside (to save a screenshot of the visualization)
    inline void getPaint(){
        this->paintGL();
    }

    /// number of clusters
    inline void setNclus(){
        numClusters=0;
        for(unsigned int a=0;a<mesh.getTopSimplexesNum();a++){
            if(numClusters < clusterIndex[a])
                numClusters=clusterIndex[a];
        }
        numClusters++;
    }

    inline void setTypeOfVisualization(unsigned int tp){
        this->typeV = tp % 3;
    }

signals:
    
public slots:

private:

    string meshFile;
    string segFile;

    Mesh<Vertex3D, Triangle> mesh;

    //Stores the indices of the segments
    int* clusterIndex;

    /// Type of visualization (0=normal, 1=fading, 2=concavities)
    unsigned int typeV;

    /// bounding box diagonal's length
    void getBBDiagonal();
    /// coordinates of the center of the mesh
    void getCenterMesh();


    //Load method
    void findMExtension(string);

    //GL methods
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);

    /// Function to draw the mesh
    void draw_mesh();
    void draw_triangle(Triangle, int f);
    void setColor(int);
    /// Reads the indices of each face from a file
    void readSegmFromFile(string);
    /// Saves the image to a .png file
    void saveImage();

    //number of regions
    int numClusters;
    //Length of the diagonal
    float diagonal;
    Vertex3D minCoord, maxCoord;
    //Approximate centroid of the object
    Vertex3D baryCenter;

    vector<Normals> normals;

    //mouse position
    QPoint lPos;

    //object rotation
    GLfloat objRX;
    GLfloat objRY;
    GLfloat objRZ;

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;

    //object position
    GLfloat objPX;
    GLfloat objPY;
    GLfloat objPZ;

};

#endif // MESHVISUALIZER_H
