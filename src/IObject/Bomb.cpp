//
// EPITECH PROJECT, 2018
// Bomb
// File description:
// Bomb
//

#include "Bomb.hpp"

Bomb::Bomb(irr::video::IVideoDriver *driver, irr::scene::ISceneManager *sceneManager,
	   irr::scene::ITriangleSelector **selector, int power)
	:IObject(false, false)
{
	_timer = 2.0;
	_power = power;
	_has_exploded = false;
	if (driver == nullptr || sceneManager == nullptr)
		return ;
	_mesh = sceneManager->addAnimatedMeshSceneNode(
		sceneManager->getMesh(FILEPATH "media/Bomb/bomb.obj"), 0,
		isDESTRUCTIBLE);
	_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_mesh->setRotation(irr::core::vector3df(0, Tools::getNbrRandom(0, 4) *
						   90, 0));
	_mesh->setScale(irr::core::vector3df(0.27, 0.27, 0.27));
	*selector = sceneManager->createTriangleSelector(
		(irr::scene::IAnimatedMeshSceneNode*)_mesh);
	_mesh->setTriangleSelector(*selector);
	_ScManager = sceneManager;
	_Driv = driver;
	_type = Type::T_BOMB;
	_effect = Effect::NOTHING;
	_explosions[0] = FILEPATH "media/musics/Explosion1.wav";
	_explosions[1] = FILEPATH "media/musics/Explosion2.wav";
	_explosions[2] = FILEPATH "media/musics/Explosion3.wav";
	_explosions[3] = FILEPATH "media/musics/Explosion4.wav";
	_explosions[4] = FILEPATH "media/musics/Explosion5.wav";
}

Bomb::~Bomb()
{
	//std::cout << "bomb destroyed" << std::endl;
	//_mesh->remove();
}

void Bomb::setPosition(irr::core::vector3df pos)
{
	_mesh->setPosition(pos);
}

void Bomb::DropObject()
{
	_mesh->drop();
}

void Bomb::runAction(irr::scene::ITriangleSelector **selector, irr::f32 fdt)
{
	Fire *fire = new Fire(_Driv, _ScManager, selector);
	fire->setPosition(_mesh->getPosition());
	(void)fdt;
	(void)selector;
}


void Bomb::explode()
{
	/*
	Fire *fire = new Fire(_Driv, _ScManager, nullptr);

	fire->setPosition(_mesh->getPosition());
	*/
	//_mesh->remove();
	//_mesh = fire->getMesh();

	_Particle = _ScManager->addParticleSystemSceneNode(false);
	_Particle->setPosition(_mesh->getPosition());

        irr::scene::IParticleEmitter* em = _Particle->createBoxEmitter(
                irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
                irr::core::vector3df(0.0001f,0.0004f,0.0001f),
                80,100,
                irr::video::SColor(0,255,255,255),
                irr::video::SColor(0,255,255,255),
                800,2000,0,
                irr::core::dimension2df(0.1f,0.1f),
                irr::core::dimension2df(2.f,2.f));

        _Particle->setEmitter(em);
        em->drop();

        irr::scene::IParticleAffector* paf = _Particle->createFadeOutParticleAffector();

        _Particle->addAffector(paf);
        paf->drop();
  
        _Particle->setScale(irr::core::vector3df(0.002, 0.002, 0.001));
        _Particle->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _Particle->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
        _Particle->setMaterialTexture(0, _Driv->getTexture(
        	FILEPATH "media/fire/fireball.bmp"));
        _Particle->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	_fdt = 0;
	_mesh->remove();
	_mesh = _Particle;
	music->play2D(_explosions[rand() % 5].c_str());
}
/*
void Bomb::frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector)
{
	if (_fdt <= 1 && 1 <= _fdt + frameDeltaTime){
		Fire *fire = new Fire(_Driv, _ScManager, selector);
		(void)fire;
	}
	//std::cout << "coucou" << std::endl;
	_mesh->remove();
	_mesh = _Particle;
	_fdt = 0;
        //(void)selector;
	//(void)driver;
}
*/
void Bomb::frame(irr::f32 frameDeltaTime, irr::scene::ITriangleSelector **selector)
{
	(void)selector;
	if (_effect == Effect::EXPLODE || _has_exploded == true){
		/**/
		//_effect = Effect::NOTHING;
		//_has_exploded = true;
		/**/
		if (_fdt > 0.5)
			_mesh->setID(ObjectType::isDESTROYED);
	}
	else if (_fdt <= _timer && _timer <= _fdt + frameDeltaTime && _effect != Effect::EXPLODE){
		setEffect(Effect::EXPLODE);
	}
	_fdt += frameDeltaTime;
}

void Bomb::setEffect(const Effect effect)
{
	if (effect == Effect::EXPLODE && _effect != Effect::EXPLODE){
		explode();
	}
	IObject::setEffect(effect);
}

void Bomb::setTimer(const irr::f32 timer)
{
	_timer = timer;
}

IObject::Effect Bomb::getEffect()
{
	IObject::Effect effect = IObject::getEffect();

	if (_has_exploded == true)
		return (IObject::Effect::NOTHING);
	if (effect == IObject::Effect::EXPLODE){
		_has_exploded = true;
	}
	return (effect);
}
