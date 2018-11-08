//
// EPITECH PROJECT, 2018
// Scene
// File description:
// Scene
//

#ifndef CSceneNodePerso
# define CSceneNodePerso

#include <irrlicht/irrlicht.h>

namespace irr
{
namespace scene
{


class CSceneNodePerso : public irr::scene::ISceneNode
{

public:

    CSceneNodePerso(irr::scene::ISceneNode* parent,
        irr::scene::ISceneManager* mgr, s32 id=0);

    virtual void OnRegisterSceneNode();            
    virtual void render();                         

    virtual const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
    virtual irr::u32 getMaterialCount() const;
    virtual irr::video::SMaterial& getMaterial(irr::u32 i);


private :

    irr::core::aabbox3d<irr::f32> m_box;           
    irr::video::SMaterial m_material;              
};


}  // end of scene namespace
}  // end of irr namespace

#endif
