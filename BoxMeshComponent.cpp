#include "BoxMeshComponent.h"

BoxMeshComponent::BoxMeshComponent(GLuint shaderProgram, Material material, float width, float height, float depth, int updateOrder)
	: boxMat(material), MeshComponent(shaderProgram, updateOrder),
	halfWidth(width / 2.0f), halfHeight(height / 2.0f), halfDepth(depth / 2.0f)
{

}


void BoxMeshComponent::buildMesh()
{
    this->scaleMeshName = "Box " + std::to_string(halfWidth) + " " +
        std::to_string(halfHeight) + " " + std::to_string(halfDepth) + std::to_string(this->boxMat._id);

    if (!previsouslyLoaded()) {
        std::vector<pntVertexData> vData;
        std::vector<unsigned int> indices;

        vec4 v1(-halfWidth, -halfHeight, halfDepth, 1.0f);
        vec4 v2(halfWidth, -halfHeight, halfDepth, 1.0f);
        vec4 v3(halfWidth, halfHeight, halfDepth, 1.0f);
        vec4 v4(-halfWidth, halfHeight, halfDepth, 1.0f);
        vec4 v5(-halfWidth, -halfHeight, -halfDepth, 1.0f);
        vec4 v6(halfWidth, -halfHeight, -halfDepth, 1.0f);
        vec4 v7(halfWidth, halfHeight, -halfDepth, 1.0f);
        vec4 v8(-halfWidth, halfHeight, -halfDepth, 1.0f);

        vec3 n1(0, 0, 1);  // +Z
        vec3 n2(0, 0, -1); // -Z
        vec3 n3(1, 0, 0);  // +X
        vec3 n4(-1, 0, 0); // -X
        vec3 n5(0, -1, 0); // -Y
        vec3 n6(0, 1, 0);  // +Y

        // Texture coordinates
        vec2 t1(0, 1); // Top-left
        vec2 t2(1, 1); // Top-right
        vec2 t3(1, 0); // Bottom-right
        vec2 t4(0, 0); // Bottom-left

        // Front face (+Z)
        vData.push_back(pntVertexData(v1, n1, t4)); // Bottom-left
        vData.push_back(pntVertexData(v2, n1, t3)); // Bottom-right
        vData.push_back(pntVertexData(v3, n1, t2)); // Top-right
        vData.push_back(pntVertexData(v4, n1, t1)); // Top-left

        // Right face (+X)
        vData.push_back(pntVertexData(v2, n3, t1)); // v2
        vData.push_back(pntVertexData(v6, n3, t2)); // v6
        vData.push_back(pntVertexData(v7, n3, t3)); // v7
        vData.push_back(pntVertexData(v3, n3, t4)); // v3

        // Left face (-X) - Single texture
        vData.push_back(pntVertexData(v5, n4, t1)); // v5
        vData.push_back(pntVertexData(v1, n4, t2)); // v1
        vData.push_back(pntVertexData(v4, n4, t3)); // v4
        vData.push_back(pntVertexData(v8, n4, t4)); // v8

        // Back face (-Z) - Inverted texture
        vData.push_back(pntVertexData(v8, n2, t1)); // v8
        vData.push_back(pntVertexData(v7, n2, t2)); // v7
        vData.push_back(pntVertexData(v6, n2, t3)); // v6
        vData.push_back(pntVertexData(v5, n2, t4)); // v5

        // Top face (+Y) - Four copies of texture
        vData.push_back(pntVertexData(v4, n6, t4 * 2.0f)); // v4
        vData.push_back(pntVertexData(v3, n6, t3 * 2.0f)); // v3
        vData.push_back(pntVertexData(v7, n6, t2 * 2.0f)); // v7
        vData.push_back(pntVertexData(v8, n6, t1 * 2.0f)); // v8

        // Bottom face (-Y) - Two copies of texture
        vData.push_back(pntVertexData(v6, n5, t1 * 1.33f));
        vData.push_back(pntVertexData(v2, n5, t2 * 1.33f));  
        vData.push_back(pntVertexData(v1, n5, t3 * 1.33f)); 
        vData.push_back(pntVertexData(v5, n5, t4 * 1.33f));

        // Indices for the triangles
        for (int i = 0; i < 6; i++) {
            indices.push_back(0 + 4 * i);
            indices.push_back(1 + 4 * i);
            indices.push_back(2 + 4 * i);
            indices.push_back(2 + 4 * i);
            indices.push_back(3 + 4 * i);
            indices.push_back(0 + 4 * i);
        }

        SubMesh boxMesh = MeshComponent::buildSubMesh(vData, indices);
        boxMesh.material = this->boxMat;
        this->subMeshes.push_back(boxMesh);

        this->collisionShape = new btBoxShape(btVector3(halfWidth, halfHeight, halfDepth));
        this->saveInitialLoad();
    }
}






