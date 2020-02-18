#include "skydome.h"



skydome::skydome() {
    tetrahedron(NumTimesToSubdivide);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(normals), normals);

    shader = new Shader("skydome.vs","skydome.fs");
    shader->use();
    GLuint program = shader->ID;


    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation(program , "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

    point4 light_position(0.0, 0.0, 2.0, 0.0);
    color4 light_ambient(0.2, 0.2, 0.2, 1.0);
    color4 light_diffuse(0.7, 0.7, 0.7, 1.0);
    color4 light_specular(1.0, 1.0, 1.0, 1.0);

    color4 material_ambient(1.0, 0.0, 1.0, 1.0);
    color4 material_diffuse(1.0, 117.0 / 255.0, 24.0 / 255.0, 1.0);
    color4 material_specular(1.0, 117.0 / 255.0, 24.0 / 255.0, 1.0);
    float  material_shininess = 5.0;

    color4 ambient_product = light_ambient * material_ambient;
    color4 diffuse_product = light_diffuse * material_diffuse;
    color4 specular_product = light_specular * material_specular;

    glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
    glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
    glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);

    glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);

    glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);

    ModelView = glGetUniformLocation(program, "ModelView");
    Projection = glGetUniformLocation(program, "Projection");
}

void skydome::draw() {
    shader->use();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void skydome::update() {
   
    point4 at(0.0, 0.0, 0.0, 1.0);
    vec4   up(0.0, 1.0, 0.0, 0.0);

    static int last_time = glutGet(GLUT_ELAPSED_TIME);

    int delta_time = glutGet(GLUT_ELAPSED_TIME) - last_time;
    last_time = glutGet(GLUT_ELAPSED_TIME);

    rotation += rot_incr * delta_time / 1000.0;
    GLfloat z = 4.0 * cos(rotation);
    GLfloat x = 4.0 * sin(rotation);
    point4 eye(x, 0.0, z, 1.0);

    mat4 model_view = LookAt(eye, at, up);
    glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);
}

void skydome::triangle(const point4& a, const point4& b, const point4& c)
{
    vec4  normal = normalize(cross(b - a, c - b));

    normals[Index] = normal;  points[Index] = a;  Index++;
    normals[Index] = normal;  points[Index] = b;  Index++;
    normals[Index] = normal;  points[Index] = c;  Index++;
}


point4 skydome::unit(const point4& p)
{
    float len = p.x * p.x + p.y * p.y + p.z * p.z;

    point4 t;
    if (len > DivideByZeroTolerance) {
        t = p / sqrt(len);
        t.w = 1.0;
    }

    return t;
}


void skydome::divide_triangle(const point4& a, const point4& b,
    const point4& c, int count)
{
    if (count > 0) {
        point4 v1 = unit(a + b);
        point4 v2 = unit(a + c);
        point4 v3 = unit(b + c);
        divide_triangle(a, v1, v2, count - 1);
        divide_triangle(c, v2, v3, count - 1);
        divide_triangle(b, v3, v1, count - 1);
        divide_triangle(v1, v3, v2, count - 1);
    }
    else {
        triangle(a, b, c);
    }
}


void skydome::tetrahedron(int count)
{
    point4 v[4] = {
      vec4(0.0, 0.0, 1.0, 1.0),
      vec4(0.0, 0.942809, -0.333333, 1.0),
      vec4(-0.816497, -0.471405, -0.333333, 1.0),
      vec4(0.816497, -0.471405, -0.333333, 1.0)
    };

    divide_triangle(v[0], v[1], v[2], count);
    divide_triangle(v[3], v[2], v[1], count);
    divide_triangle(v[0], v[3], v[1], count);
    divide_triangle(v[0], v[2], v[3], count);
}

void skydome::reshape(int width, int height)
{
    glViewport(0, 0, width, height);

    GLfloat left = -2.0, right = 2.0;
    GLfloat top = 2.0, bottom = -2.0;
    //  GLfloat zNear = -20.0, zFar = 20.0;
    GLfloat zNear = 2.0, zFar = 20.0;

    GLfloat aspect = GLfloat(width) / height;

    if (aspect > 1.0) {
        left *= aspect;
        right *= aspect;
    }
    else {
        top /= aspect;
        bottom /= aspect;
    }

    mat4 projection = Perspective(45.0, aspect, zNear, zFar);
    //  mat4 projection = Ortho(left, right, bottom, top, zNear, zFar);
    glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
}
