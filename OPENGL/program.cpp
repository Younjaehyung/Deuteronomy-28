#include "program.h"

ProgramUPtr Program::Create ( const std::vector<ShaderPtr>& shaders )
{

	auto program = ProgramUPtr ( new Program ( ) );
	if ( !program->link ( shaders ) )
		return nullptr;

	return std::move ( program );
}




ProgramUPtr Program::Create (const std::string& vertShaderFilename ,const std::string& fragShaderFilename ) {
	ShaderPtr vs = Shader::CreateFromFile ( vertShaderFilename ,GL_VERTEX_SHADER );
	ShaderPtr fs = Shader::CreateFromFile ( fragShaderFilename ,GL_FRAGMENT_SHADER );
	if ( !vs || !fs )
		return nullptr;
	std::cerr << "vertex shader id: " << vs->Get ( ) << std::endl;
	std::cerr << "fragment shader id: " << fs->Get ( ) << std::endl;


	return std::move ( Create ( { vs, fs } ) );
}

Program::~Program ( )
{
	if ( m_program ) {
		glDeleteProgram ( m_program );	//program object 제거
	}
}

void Program::Use ( ) const
{
	glUseProgram ( m_program );
}

//프로그램, shader 링크
bool Program::link ( const std::vector<ShaderPtr>& shaders )
{
	
		m_program = glCreateProgram ( );	//OpenGL program object 생성
		for ( auto& shader : shaders )
			glAttachShader ( m_program , shader->Get ( ) );	//program에 shader를 붙이기
		glLinkProgram ( m_program );	//program 링크
	
		int success = 0;
		glGetProgramiv ( m_program , GL_LINK_STATUS , &success );	//program에 대한 정수형 정보를 얻어옴
		if ( !success ) {
			char infoLog[ 1024 ];
			glGetProgramInfoLog ( m_program , 1024 , nullptr , infoLog );	//program에 대한 로그를 얻어옴. 링크 에러 얻어내는 용도
			std::cout<<"failed to link program:" << infoLog <<std::endl;	
			return false;
		}
		return true;
}

//uniform 변수에 값 입력
void Program::SetUniform ( const std::string& name , int value ) const {
	auto loc = glGetUniformLocation ( m_program , name.c_str ( ) );
	glUniform1i ( loc , value );
}

void Program::SetUniform ( const std::string& name ,const glm::mat4& value ) const {
	auto loc = glGetUniformLocation ( m_program , name.c_str ( ) );
	glUniformMatrix4fv ( loc , 1 , GL_FALSE , glm::value_ptr ( value ) );
}

void Program::SetUniform ( const std::string& name , float value ) const {
	auto loc = glGetUniformLocation ( m_program , name.c_str ( ) );
	glUniform1f ( loc , value );
}

void Program::SetUniform ( const std::string& name , const glm::vec3& value ) const {
	auto loc = glGetUniformLocation ( m_program , name.c_str ( ) );
	glUniform3fv ( loc , 1 , glm::value_ptr ( value ) );
}

void Program::SetUniform ( const std::string& name ,const glm::vec4& value ) const {
	auto loc = glGetUniformLocation ( m_program , name.c_str ( ) );
	glUniform4fv ( loc , 1 , glm::value_ptr ( value ) );
}

void Program::SetUniform ( const std::string& name , const glm::vec2& value ) const {
	auto loc = glGetUniformLocation ( m_program , name.c_str ( ) );
	glUniform2fv ( loc , 1 , glm::value_ptr ( value ) );
}
