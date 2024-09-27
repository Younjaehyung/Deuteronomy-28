#pragma once

#include "common_include.h"
#include "shader.h"

CLASS_PTR(Program)

/*
vertex, fragment shader 외에 여래 개의 shader을 링크할 수도 있게 함
shader 인스턴스 인자는 필요하지만 소유할 필요는 없음
shader 인스턴스는 다른 program 인스턴스를 만드는 데 재사용할 수도 있음
따라서 shader pointer를 사용: shaderptr

*/


class Program
{
public:
	static ProgramUPtr Create ( const std::vector<ShaderPtr>& shaders);
	static ProgramUPtr Create ( const std::string& vertShaderFilename ,const std::string& fragShaderFilename );



	~Program ( );
	uint32_t Get ( ) const { return m_program; }
	void Use ( ) const;

	
	void SetUniform ( const std::string& name , int value ) const;
	void SetUniform ( const std::string& name , float value ) const;
	void SetUniform ( const std::string& name , const glm::vec2& value ) const;
	void SetUniform ( const std::string& name , const glm::vec3& value ) const;
	void SetUniform ( const std::string& name , const glm::vec4& value ) const;
	void SetUniform ( const std::string& name , const glm::mat4& value ) const;

	template<typename T>
	static bool UserSetError ( T& value ) {
		if ( !value ) {
			std::cerr << "program UserSetError id : " << value->Get ( ) << std::endl;
			return false;
			

		}
	}
private:
	Program ( ) {}
	bool link ( const std::vector<ShaderPtr>& shaders );
	uint32_t m_program{ 0 };

};