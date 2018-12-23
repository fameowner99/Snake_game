/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:42:55 by anesteru          #+#    #+#             */
/*   Updated: 2018/11/06 16:42:56 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tilemap.hpp"

TileMap::TileMap(const int *tiles, int width, int height) : tiles(tiles), width(width), height(height)
{
	this->m_vertices.setPrimitiveType(sf::Quads);
	this->m_vertices.resize(width * height * 4);
	this->m_tileSize = sf::Vector2u(100, 100);
}

TileMap::~TileMap(void) {}

bool	TileMap::load(const std::string &tileset)
{
	return (m_tileset.loadFromFile(tileset));
}

void	TileMap::redraw(void)
{
	for (int i = 0; i < this->width; i++)
	{
		for (int j = 0; j < this->height; j++)
		{
			// get the current tile number
			int tileNumber = tiles[i + j * this->width];

			// find its position in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * this->width) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
			quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
		}
	}
}

void	TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
}
