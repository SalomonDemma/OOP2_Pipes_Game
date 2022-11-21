#pragma once

#include "EnumAndConst.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using sf::Font;
using sf::Texture;
using std::ifstream;
using std::vector;
using std::ostringstream;
using sf::SoundBuffer;


class Resources {

public:
	//----------Destructor-------------------------
	~Resources();
	static Resources& instance();

	//----------Get Font----------------------
	const Font& getfont() const;

	//----------Get Texture----------------------
	const Texture& getMenuBackground()	const;
	const Texture& getBoardBackground()	const;
	const Texture& getStartButton()		const;
	const Texture& getExitButton()		const;
	const Texture& getFaucet()			const;
	const Texture& getSink()			const;
	const Texture& getPipe1()			const;
	const Texture& getPipe2()			const;
	const Texture& getPipe3()			const;
	const Texture& getPipe4()			const;
	const Texture& getFullPipe1()		const;
	const Texture& getFullPipe2()		const;
	const Texture& getFullPipe3()		const;
	const Texture& getFullPipe4()		const;


	////----------Get Sound----------------------



private:
	//Constructor
	Resources();

	//Private Funcs
	Resources(const Resources&) = default;
	Resources& operator= (const Resources&) = default;

	//----------Load Funcs----------------------
	void loadresources();
	void loadtextures();
	void loadfont();

	//Private Members
	sf::Font						m_fontType;		     //Font for the text messeges
	std::vector <sf::Texture>		m_textures;			 //Object textures

};