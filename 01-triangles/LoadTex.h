#pragma once
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>

using namespace std;

GLuint LoadTex(string imagepath) {
    cv::Mat pic = cv::imread(imagepath, cv::IMREAD_COLOR);
    cv::flip(pic, pic, 0);
    cout << "Reading image " << imagepath << "\n";

    unsigned int width = pic.size().width;
    unsigned int height = pic.size().height;

    // Create one OpenGL texture
    GLuint* textureID=new GLuint;
    glGenTextures(1, textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, *textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pic.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    return *textureID;
}

