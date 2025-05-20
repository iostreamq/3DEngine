#include <Renderer/OpenGL/Shaders/ShaderProgram.hpp>
#include <3DEngineCore/Log.hpp>

Engine::ShaderProgram::ShaderProgram(const ShaderDesc& vertexDesc, const ShaderDesc& fragmentDesc)
	:m_vertexShader(std::make_unique<Shader>())
	,m_fragmentShader(std::make_unique<Shader>())
	,m_id(0)
	,m_isCompiled(false)
{
	m_vertexShader->createShader(vertexDesc, GL_VERTEX_SHADER);
	if (!m_vertexShader->checkCompileStatus())
		return;

	m_fragmentShader->createShader(fragmentDesc, GL_FRAGMENT_SHADER);
	if (!m_fragmentShader->checkCompileStatus())
		return;

	createProgram();
}

void Engine::ShaderProgram::createProgram()
{
	m_id = glCreateProgram();
	glAttachShader(m_id, m_vertexShader->getId());
	glAttachShader(m_id, m_fragmentShader->getId());
	glLinkProgram(m_id);
}

bool Engine::ShaderProgram::checkCompileStatus()
{
	GLint success;
	glGetProgramiv(m_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetProgramInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
		LOG_CRIT("ERROR::SHADER_PROGRAM: Link-time error:{}", infoLog);
		m_isCompiled = false;
	}
	else
		m_isCompiled = true;
	
	return m_isCompiled;
}

void Engine::ShaderProgram::deleteShaders()
{
	glDetachShader(m_id, m_vertexShader->getId());
	glDetachShader(m_id, m_fragmentShader->getId());
	glDeleteShader(m_vertexShader->getId());
	glDeleteShader(m_fragmentShader->getId());
}

void Engine::ShaderProgram::bind() { glUseProgram(m_id); }

void Engine::ShaderProgram::unbind() { glUseProgram(0) ;}

Engine::ShaderProgram::~ShaderProgram() { glDeleteProgram(m_id); }
