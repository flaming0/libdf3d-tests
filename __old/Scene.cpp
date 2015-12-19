#include "Scene.h"

#include <utils/Utils.h>
#include <scene/Node.h>
#include <render/RenderStats.h>
#include <components/ParticleSystemComponent.h>

namespace df3d {

Scene::Scene()
    : m_root(make_shared<Node>("__root"))
{
}

Scene::~Scene()
{
}

void Scene::setAmbientLight(float ra, float ga, float ba)
{
    m_ambientLight.r = utils::clamp(ra, 0.0f, 1.0f);
    m_ambientLight.g = utils::clamp(ga, 0.0f, 1.0f);
    m_ambientLight.b = utils::clamp(ba, 0.0f, 1.0f);
}

glm::vec3 Scene::getAmbientLight() const
{
    return m_ambientLight;
}

void Scene::setFog(float density, const glm::vec3 &color)
{
    m_fogDensity = density;
    m_fogColor = color;
}

void Scene::setFog(float density, float r, float g, float b)
{
    setFog(density, glm::vec3(r, g, b));
}

float Scene::getFogDensity() const
{
    return m_fogDensity;
}

glm::vec3 Scene::getFogColor() const
{
    return m_fogColor;
}

void Scene::setPostProcessMaterial(shared_ptr<Material> material)
{
    m_postProcessMaterial = material;
}

shared_ptr<Node> Scene::getChildByName(const std::string &name) const
{
    return m_root->getChildByName(name);
}

void Scene::addChild(shared_ptr<Node> child)
{
    m_root->addChild(child);
}

void Scene::removeChild(shared_ptr<Node> child)
{
    m_root->removeChild(child);
}

void Scene::removeChild(const std::string &name)
{
    m_root->removeChild(name);
}

void Scene::removeAllChildren()
{
    m_root->removeAllChildren();
}

}
