#include "gameover.h"

void gameover::Update ( )
{


}

bool gameover::Initialize ( )
{
    m_simpleProgram = Program::Create ( "./shader/simple.vs" , "./shader/simple.fs" );
    if ( !m_simpleProgram ) {
        //std::cerr << "program UserSetError id : " << m_simpleProgram->Get ( ) << std::endl;
        return false;


    }

    m_program = Program::Create ( "./shader/lighting.vs" , "./shader/lighting.fs" );
    if ( !m_program ) {
       // std::cerr << "program UserSetError id : " << m_program->Get ( ) << std::endl;
        return false;


    }

    m_simpleAnimationProgram = Program::Create ( "./shader/lighting.vs" , "./shader/lighting.fs" );
    if ( !m_program ) {
       // std::cerr << "program UserSetError id : " << m_program->Get ( ) << std::endl;
        return false;


    }


}

void gameover::ProcessInput ( )
{
}

void gameover::FixedUpdate ( )
{
}

void gameover::Render ( )
{
	//m_program->Use ( );

}
