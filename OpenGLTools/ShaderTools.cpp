#include "ShaderTools.h"

/* Shader Program Helper
 This function will attempt to create a shader program that has
 the Vertex and Fragement shader code that you pass in. If successfully
 compiled and linked to the program, the unique program ID given by
 OpenGL will be returned. This ID will be >1 if successful, or 0 (an
 invalid ID) if any of the above fails.

 Most of the Code below is for checking if the shaders compiled and
 linked correctly.
 */
GLuint CreateShaderProgram(const std::string &vsSource,
                           const std::string &fsSource) {
  GLuint programID = glCreateProgram();
  GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
  GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);

  if (programID == 0 || vsID == 0 || fsID == 0) {
    // Clean up others that were created
    glDeleteProgram(programID);
    glDeleteShader(vsID);
    glDeleteShader(fsID);

    std::cerr << "Cannot create Shaders or Program" << std::endl;
    return 0; // invalid ID
  }

  // glShaderSource() expects char**, so these are helper variables
  const char *vsSourceArray = vsSource.c_str();
  const char *fsSourceArray = fsSource.c_str();

  // https://www.opengl.org/sdk/docs/man4/xhtml/glShaderSource.xml
  glShaderSource(vsID, 1, &vsSourceArray, NULL);

  glShaderSource(fsID, 1, &fsSourceArray, NULL);

  // Compile the Shader Sources, check for errors
  glCompileShader(vsID);
  glCompileShader(fsID);

  if (!checkCompileStatus(vsID) || !checkCompileStatus(fsID)) {
    // Clean up others that were created
    glDeleteProgram(programID);
    glDeleteShader(vsID);
    glDeleteShader(fsID);

    std::cerr << "Cannot create Shaders or Program" << std::endl;
    return 0; // invalid ID
  }

  glAttachShader(programID, vsID);
  glAttachShader(programID, fsID);

  glLinkProgram(programID);

  if (!checkLinkStatus(programID)) {
    // Clean up others that were created
    glDeleteProgram(programID);
    glDeleteShader(vsID);
    glDeleteShader(fsID);

    std::cerr << "Cannot create Shaders or Program" << std::endl;
    return 0; // invalid ID
  }

  return programID;
}

GLuint CreateShaderProgram(const std::string &vsSource,
                           const std::string &gsSource,
                           const std::string &fsSource) {
  GLuint programID = glCreateProgram();
  GLuint vsID = glCreateShader(GL_VERTEX_SHADER);
  GLuint gsID = glCreateShader(GL_GEOMETRY_SHADER);
  GLuint fsID = glCreateShader(GL_FRAGMENT_SHADER);

  if (programID == 0 || vsID == 0 || gsID == 0 || fsID == 0) {
    // Clean up others that were created
    glDeleteProgram(programID);
    glDeleteShader(vsID);
    glDeleteShader(gsID);
    glDeleteShader(fsID);

    std::cerr << "Cannot create Shaders or Program" << std::endl;
    return 0; // invalid ID
  }

  // glShaderSource() expects char**, so these are helper variables
  const char *vsSourceArray = vsSource.c_str();
  const char *gsSourceArray = gsSource.c_str();
  const char *fsSourceArray = fsSource.c_str();

  // https://www.opengl.org/sdk/docs/man4/xhtml/glShaderSource.xml
  glShaderSource(vsID, 1, &vsSourceArray, NULL);

  glShaderSource(gsID, 1, &gsSourceArray, NULL);

  glShaderSource(fsID, 1, &fsSourceArray, NULL);

  // Compile the Shader Sources, check for errors
  glCompileShader(vsID);
  glCompileShader(gsID);
  glCompileShader(fsID);

  if (!checkCompileStatus(vsID) || !checkCompileStatus(fsID) ||
      !checkCompileStatus(gsID)) {
    // Clean up others that were created
    glDeleteProgram(programID);
    glDeleteShader(vsID);
    glDeleteShader(gsID);
    glDeleteShader(fsID);

    std::cerr << "Cannot Compile Shaders or Program" << std::endl;
    return 0; // invalid ID
  }

  glAttachShader(programID, vsID);
  glAttachShader(programID, gsID);
  glAttachShader(programID, fsID);

  glLinkProgram(programID);

  if (!checkLinkStatus(programID)) {
    // Clean up others that were created
    glDeleteProgram(programID);
    glDeleteShader(vsID);
    glDeleteShader(gsID);
    glDeleteShader(fsID);

    std::cerr << "Cannot Link Shaders or Program" << std::endl;
    return 0; // invalid ID
  }

  return programID;
}

bool checkLinkStatus(GLint programID) {
  GLint result;
  int infoLogLength;
  glGetProgramiv(programID, GL_LINK_STATUS, &result);
  if (!result) {
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> errorMsg(infoLogLength);
    glGetProgramInfoLog(programID, infoLogLength, NULL, errorMsg.data());
    std::cerr << errorMsg.data() << std::endl;
    return false;
  }
  return true;
}

bool checkCompileStatus(GLint shaderID) {
  GLint result;
  int infoLogLength;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
  if (!result) {
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> errorMsg(infoLogLength);
    glGetShaderInfoLog(shaderID, infoLogLength, NULL, errorMsg.data());
    std::cerr << errorMsg.data() << std::endl;
    return false;
  }
  return true; // otherwise
}

// Returns Empty String if can't load from file
std::string loadShaderStringfromFile(const std::string &filePath) {
  std::string shaderCode;
  std::ifstream fileStream(filePath.c_str(), std::ios::in);
  if (fileStream.is_open()) {
    std::string line;
    while (std::getline(fileStream, line)) {
      shaderCode += "\n" + line;
    }
    fileStream.close();

  } else {
    std::cerr << "Could Not Open File " << filePath << std::endl;
  }
  return shaderCode;
}
