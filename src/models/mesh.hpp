//
// Created by karl on 13.03.21.
//

#ifndef INC_3CARDRENDERER_MESH_HPP
#define INC_3CARDRENDERER_MESH_HPP


#include "../GL/camera.hpp"
#include "../GL/shader.hpp"
#include "../GL/elementBuffer.hpp"
#include "../GL/buffer.hpp"
#include "../GL/vertexArray.hpp"

class mesh {
public:
    mesh(const bufferData &vbo, const elementBufferData &ebo, const vertexArrayData *vao, const shaderPath &sh,
         uint8_t vaoCount = 1);

    void update(const camera &cam);

    void setModel(const glm::mat4 &model);

    void render();

private:
    buffer m_buffer;
    elementBuffer m_elementBuffer;
    vertexArray m_vertexArray;
    shader m_sh;

};


#endif //INC_3CARDRENDERER_MESH_HPP
