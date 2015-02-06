/* 
 * File:   Object.cpp
 * Author: Lukas
 * 
 * Created on Sobota, 2015, január 17, 18:50
 */

#include "GObject.h"

GObject::GObject(TypeOfObject objectType,TypeOfShader shaderType):objectType(objectType),shaderType(shaderType) {
    if(this->objectType==CUBE){
        mesh=new Mesh();
        mesh->loadCube();
    }
    if(this->shaderType==TEXTURECLASSIC){
        activeShader=new Shader();
        activeShader->loadShader();
    }
    transformation = new Transformation();
}

TypeOfObject GObject::getObjectType() const {
        return objectType;
}

void GObject::setObjectType(TypeOfObject objectType) {
    this->objectType = objectType;
}

TypeOfShader GObject::getShaderType() const {
    return shaderType;
}

void GObject::setShaderType(TypeOfShader shaderType) {
    this->shaderType = shaderType;
}

void GObject::setTextures(char* front,char* back,char* left,char* right,char* top ,char* bottom){
    if(back==NULL){
        textures[0].loadTexture(activeShader->getShaderProgram(),front);
    }
    else{
        textures[0].loadTexture(activeShader->getShaderProgram(),front);
        textures[1].loadTexture(activeShader->getShaderProgram(),back);
        textures[2].loadTexture(activeShader->getShaderProgram(),left);
        textures[3].loadTexture(activeShader->getShaderProgram(),right);
        textures[4].loadTexture(activeShader->getShaderProgram(),top);
        textures[5].loadTexture(activeShader->getShaderProgram(),bottom);
    }
}
void GObject::move(float ammountX, float ammountY, float ammountZ){
    transformation->move(ammountX,ammountY,ammountZ);  
}

void GObject::rotate(float ammountX ,float ammountY,float ammountZ){
    transformation->rotate(ammountX,ammountY,ammountZ);         
}

void GObject::drawTo(float x,float y,float z){
    transformation->move(x,y,z);
    transformation->apply(activeShader->getShaderProgram());
    if(textures[1].isUsed()){
        textures[0].bindTexture();
        mesh->selectCubeFront();
        mesh->draw(activeShader->getShaderProgram());
        textures[1].bindTexture();
        mesh->selectCubeBack();
        mesh->draw(activeShader->getShaderProgram());
        textures[2].bindTexture();
        mesh->selectCubeLeft();
        mesh->draw(activeShader->getShaderProgram());
        textures[3].bindTexture();
        mesh->selectCubeRight();
        mesh->draw(activeShader->getShaderProgram());
        textures[4].bindTexture();
        mesh->selectCubeTop();
        mesh->draw(activeShader->getShaderProgram());
        textures[5].bindTexture();
        mesh->selectCubeBottom();
        mesh->draw(activeShader->getShaderProgram());
    }
    else{
        textures[0].bindTexture();
        mesh->selectCubeFront();
        mesh->draw(activeShader->getShaderProgram());
        mesh->selectCubeBack();
        mesh->draw(activeShader->getShaderProgram());
        mesh->selectCubeLeft();
        mesh->draw(activeShader->getShaderProgram());
        mesh->selectCubeRight();
        mesh->draw(activeShader->getShaderProgram());
        mesh->selectCubeTop();
        mesh->draw(activeShader->getShaderProgram());
        mesh->selectCubeBottom();
        mesh->draw(activeShader->getShaderProgram());
    }
}

GLuint GObject::getActiveShader(){
    return activeShader->getShaderProgram();
}

GObject::~GObject() {
    delete mesh;
    delete transformation;
    delete activeShader;
}