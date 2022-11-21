#include "Resources.h"


Resources::Resources()
{
	loadresources();
}

Resources::~Resources() {}

Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}
const Font& Resources::getfont() const
{
	return m_fontType;
}
const Texture& Resources::getMenuBackground() const
{
	return m_textures[t_MenuBackground];
}
const Texture& Resources::getBoardBackground() const
{
	return m_textures[t_BoardBackground];
}
const Texture& Resources::getStartButton() const
{
	return m_textures[t_StartButton];
}
const Texture& Resources::getExitButton() const
{
	return m_textures[t_ExitButton];
}
const Texture& Resources::getFaucet() const
{
	return m_textures[t_Faucet];
}
const Texture& Resources::getSink() const
{
	return m_textures[t_Sink];
}
const Texture& Resources::getPipe1() const
{
	return m_textures[t_Pipe1];
}
const Texture& Resources::getPipe2() const
{
	return m_textures[t_Pipe2];
}
const Texture& Resources::getPipe3() const
{
	return m_textures[t_Pipe3];
}
const Texture& Resources::getPipe4() const
{
	return m_textures[t_Pipe4];
}
const Texture& Resources::getFullPipe1() const
{
	return m_textures[t_FullPipe1];
}
const Texture& Resources::getFullPipe2() const
{
	return m_textures[t_FullPipe2];
}
const Texture& Resources::getFullPipe3() const
{
	return m_textures[t_FullPipe3];
}
const Texture& Resources::getFullPipe4() const
{
	return m_textures[t_FullPipe4];
}
void Resources::loadresources()
{
	loadtextures();
	//loadsound();
	loadfont();
}

void Resources::loadtextures()
{
	m_textures.resize(t_EmptySpace);

	m_textures[t_MenuBackground].loadFromFile("MenuBackground.png");
	m_textures[t_BoardBackground].loadFromFile("BoardBackground.png");
	m_textures[t_StartButton].loadFromFile("StartButton.png");
	m_textures[t_ExitButton].loadFromFile("ExitButton.png");
	m_textures[t_Faucet].loadFromFile("faucet.png");
	m_textures[t_Sink].loadFromFile("sink.png");
	m_textures[t_Pipe1].loadFromFile("pipe1.png");
	m_textures[t_Pipe2].loadFromFile("pipe2.png");
	m_textures[t_Pipe3].loadFromFile("pipe3.png");
	m_textures[t_Pipe4].loadFromFile("pipe4.png");
	m_textures[t_FullPipe1].loadFromFile("pipe1F.png");
	m_textures[t_FullPipe2].loadFromFile("pipe2F.png");
	m_textures[t_FullPipe3].loadFromFile("pipe3F.png");
	m_textures[t_FullPipe4].loadFromFile("pipe4F.png");
}

void Resources::loadfont()
{
	if (!m_fontType.loadFromFile("DebugFreeTrial-MVdYB.otf"))
	{// If font couldn't be loaded
		perror("cant load font");
		exit(EXIT_FAILURE);
	}
}
