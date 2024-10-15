#include "Character.h"
#include<iostream>
Font::Font() noexcept
{
	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;

	}
	if (FT_New_Face(ft, "resources/fonts/Source_Han_Serif_SC_Light_Light.otf", 0, &face)) {
	
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	fontSize =10*64;
	VAO = 0;
	VBO = 0;
	glGenVertexArrays(1, &VAO); 
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Font::~Font() noexcept
{
	// �ͷ�Face����
	FT_Done_Face(face);
	// �ͷſ�
	FT_Done_FreeType(ft);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1,&VBO);
	for (auto& chr : characters) {
		glDeleteTextures(1, &(chr.second.textureID));
	}
}
void Font::Load(const wchar_t * ch)
{
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	//ֻ���浥������
	if (FT_Load_Char(face, *ch, FT_LOAD_RENDER)) {
		std::cout << "wor";
	}
	//�����ַ��Ѿ����˸��ַ�
	if (characters.find(*ch) != characters.end())
		return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindVertexArray(VAO);
	
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		face->glyph->bitmap.width,
		face->glyph->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		face->glyph->bitmap.buffer
	);	
	// ��������ѡ��
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Character chr = {
			texture,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x
	};
	characters[*ch] = chr;
	glBindVertexArray(0);
}

void Font::Load()
{
	//����������ȫ������
	wchar_t  charcode;
	FT_UInt   gindex;
	charcode =  FT_Get_First_Char(face, &gindex);
	glBindVertexArray(VAO);
	unsigned int texture;
	while (gindex) {
		
		FT_Load_Glyph(face, gindex, FT_LOAD_RENDER);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character chr = {
			texture,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			face->glyph->bitmap_left,
			face->glyph->bitmap_top,
			face->glyph->advance.x
		};
		characters[charcode] = chr;
		charcode=FT_Get_Next_Char(face, charcode, &gindex);
	}
	glBindVertexArray(0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

