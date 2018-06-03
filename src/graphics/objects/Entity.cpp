#include "Entity.h"
#include "../../loaders/SceneLoader.h"

Entity::Entity(ShaderProgram& shaderProgram, const std::string &filePath, Material& material) :
        mesh(ModelLoader::load(shaderProgram, filePath)),
        material(material),
        scaling(1.0f)
{}

Entity::Entity(ShaderProgram& shaderProgram, Mesh* mesh, Material& material) :
        mesh(mesh),
        material(material),
        scaling(1.0f)
{}

void Entity::place(Vec3 position) {
    transformation = transformation.place(position);
}

void Entity::translate(Vec3 translation) {
    transformation = transformation.translate(translation);
}

void Entity::rotate(Vec3 rotation) {
    transformation = transformation.rotateX(rotation[0]);
    transformation = transformation.rotateY(rotation[1]);
    transformation = transformation.rotateZ(rotation[2]);
}

void Entity::scale(float scale) {
    transformation = transformation * scale;
}

void Entity::render(ShaderProgram& shaderProgram) {
    shaderProgram.set("model", transformation);
    shaderProgram.set("scale", scaling);
    shaderProgram.set("material.diffuseColor", material.diffuseColor.toVector());
    shaderProgram.set("material.specularColor", material.specularColor.toVector());
    shaderProgram.set("material.shininess", material.shininess);
    shaderProgram.set("material.intensity", material.intensity);
    shaderProgram.set("material.textured", material.textured);
    shaderProgram.set("material.sampler", 0);

    if (material.textured) {
        material.texture->bind();
        mesh->render();
        material.texture->unbind();
    } else {
        mesh->render();
    }
}
