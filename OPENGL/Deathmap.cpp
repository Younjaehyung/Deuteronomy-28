#include "Deathmap.h"
#include "LightManager.h"

void Deathmap::Update ( )
{



}

void Deathmap::Render ()
{

	LightManager::getInstance ( ).GetLightSetting ( m_simpleProgram.get() );
    m_map->Draw ( m_simpleProgram.get ( ) );

    LightManager::getInstance ( ).GetLightSetting ( m_simpleAnimationProgram.get ( ) );
    m_player->Draw ( m_simpleAnimationProgram.get ( ) );
    m_monster->Draw ( m_simpleAnimationProgram.get ( ) );

}

bool Deathmap::Initialize ()
{
    std::cerr << "DEATH MAP start " << std::endl;
    



}

