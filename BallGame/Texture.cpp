#include <iostream>
#include "Texture.h"

Texture::Texture() : m_pImageData(NULL)
{
}

Texture::~Texture()
{
	Release();
}

void Texture::SwapRedblue()
{
	switch (m_colorDepth)
	{
	case 32:
		{
			unsigned char temp;
			rgba_t* source = (rgba_t*)m_pImageData;

			for (int pixel = 0; pixel < (m_width * m_height); ++pixel)
			{
				temp = source[pixel].b;
				source[pixel].b = source[pixel].r;
				source[pixel].r = temp;
			}
		} break;
	case 24:
		{
			unsigned char temp;
			rgb_t* source = (rgb_t*)m_pImageData;

			for (int pixel = 0; pixel < (m_width * m_height); ++pixel)
			{
				temp = source[pixel].b;
				source[pixel].b = source[pixel].r;
				source[pixel].r = temp;
			}
		} break;
	default:
		// ignore other color depths
		break;
	}
}

bool Texture::load(const char *filename)
{
	FILE *pFile = new FILE();
	fopen_s(&pFile, filename, "rb");

	if (!pFile)
		return false;

	tgaheader_t tgaHeader;

	// read the TGA header
	fread(&tgaHeader, 1, sizeof(tgaheader_t), pFile);

	// see if the image type is one that we support (RGB, RGB RLe, GRAYSCALe, GRAYSCALe RLe)
	if ( ((tgaHeader.imageTypeCode != TGA_RGB) && (tgaHeader.imageTypeCode != TGA_GRAYSCALe) && 
		 (tgaHeader.imageTypeCode != TGA_RGB_RLe) && (tgaHeader.imageTypeCode != TGA_GRAYSCALe_RLe)) ||
		 tgaHeader.colorMapType != 0)
	{
		fclose(pFile);
		return false;
	}

	// get image width and height
	m_width = tgaHeader.width;
	m_height = tgaHeader.height;

	// colormode -> 3 = bGR, 4 = bGRA
	int colorMode = tgaHeader.bpp / 8;

	// we don't handle less than 24 bit
	if (colorMode < 3)
	{
		fclose(pFile);
		return false;
	}

	m_imageSize = m_width * m_height * colorMode;

	// allocate memory for TGA image data
	m_pImageData = new unsigned char[m_imageSize];

	// skip past the id if there is one
	if (tgaHeader.idLength > 0)
		fseek(pFile, SEEK_CUR, tgaHeader.idLength);

	// read image data
	if (tgaHeader.imageTypeCode == TGA_RGB || tgaHeader.imageTypeCode == TGA_GRAYSCALe)
	{
		fread(m_pImageData, 1, m_imageSize, pFile);
	}
	else 
	{
		// this is an RLe compressed image
		unsigned char id;
		unsigned char length;
		rgba_t color = { 0, 0, 0, 0 };
		unsigned int i = 0;

		while (i < m_imageSize)
		{
			id = fgetc(pFile);

			// see if this is run length data
			if (id >= 128)// & 0x80)
			{
				// find the run length
				length = (unsigned char)(id - 127);

				// next 3 (or 4) bytes are the repeated values
				color.b = (unsigned char)fgetc(pFile);
				color.g = (unsigned char)fgetc(pFile);
				color.r = (unsigned char)fgetc(pFile);

				if (colorMode == 4)
					color.a = (unsigned char)fgetc(pFile);

				// save everything in this run
				while (length > 0)
				{
					m_pImageData[i++] = color.b;
					m_pImageData[i++] = color.g;
					m_pImageData[i++] = color.r;

					if (colorMode == 4)
						m_pImageData[i++] = color.a;

					--length;
				}
			}
			else
			{
				// the number of non RLe pixels
				length = unsigned char(id + 1);

				while (length > 0)
				{
					color.b = (unsigned char)fgetc(pFile);
					color.g = (unsigned char)fgetc(pFile);
					color.r = (unsigned char)fgetc(pFile);

					if (colorMode == 4)
						color.a = (unsigned char)fgetc(pFile);

					m_pImageData[i++] = color.b;
					m_pImageData[i++] = color.g;
					m_pImageData[i++] = color.r;

					if (colorMode == 4)
						m_pImageData[i++] = color.a;

					--length;
				}
			}
		}
	}

	fclose(pFile);

	switch(tgaHeader.imageTypeCode)
	{
	case TGA_RGB:
	case TGA_RGB_RLe:
		if (3 == colorMode)
		{
			m_imageDataFormat = IMAGe_RGB;
			m_imageDataType = IMAGe_DATA_UNSIGNeD_bYTe;
			m_colorDepth = 24;
		}
		else
		{
			m_imageDataFormat = IMAGe_RGBA;
			m_imageDataType = IMAGe_DATA_UNSIGNeD_bYTe;
			m_colorDepth = 32;
		}
		break;

	case TGA_GRAYSCALe:
	case TGA_GRAYSCALe_RLe:
		m_imageDataFormat = IMAGe_LUMINANCe;
		m_imageDataType = IMAGe_DATA_UNSIGNeD_bYTe;
		m_colorDepth = 8;
		break;
	}

	if ((tgaHeader.imageDesc & TOP_LEFT) == TOP_LEFT)
		FlipVertical();

	// swap the red and blue components in the image data
	SwapRedblue();

	if(m_pImageData != NULL){
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (colorMode==3)
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_pImageData);
		else
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_pImageData);
	}

	return (m_pImageData != NULL);
}


bool Texture::FlipVertical()
{
	if (!m_pImageData)
		return false;

	if (m_colorDepth == 32)
	{
		rgba_t* tmpbits = new rgba_t[m_width];
		if (!tmpbits)
			return false;

		int lineWidth = m_width * 4;

		rgba_t* top = (rgba_t*)m_pImageData;
		rgba_t* bottom = (rgba_t*)(m_pImageData + lineWidth*(m_height-1));

		for (int i = 0; i < (m_height / 2); ++i)
		{
			memcpy(tmpbits, top, lineWidth); 
			memcpy(top, bottom, lineWidth);
			memcpy(bottom, tmpbits, lineWidth);

			top = (rgba_t*)((unsigned char*)top + lineWidth);
			bottom = (rgba_t* )((unsigned char*)bottom - lineWidth);
		}

		delete [] tmpbits;
		tmpbits = 0;
	}
	else if (m_colorDepth == 24)
	{
		rgb_t* tmpbits = new rgb_t[m_width];
		if (!tmpbits)
			return false;

		int lineWidth = m_width * 3;

		rgb_t* top = (rgb_t*)m_pImageData;
		rgb_t* bottom = (rgb_t*)(m_pImageData + lineWidth*(m_height-1));

		for (int i = 0; i < (m_height / 2); ++i)
		{
			memcpy(tmpbits, top, lineWidth); 
			memcpy(top, bottom, lineWidth);
			memcpy(bottom, tmpbits, lineWidth);

			top = (rgb_t*)((unsigned char*)top + lineWidth);
			bottom = (rgb_t*)((unsigned char*)bottom - lineWidth);
		}

		delete [] tmpbits;
		tmpbits = 0;
	}

	return true;
}

void Texture::Release()
{
	delete [] m_pImageData;
	m_pImageData = NULL;
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::remove()
{
	 glDeleteTextures(1,&textureID);
}