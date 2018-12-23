/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilemap.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anesteru <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:43:05 by anesteru          #+#    #+#             */
/*   Updated: 2018/11/06 16:43:06 by anesteru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TILEMAP_HPP
# define TILEMAP_HPP

# include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{

public:

	TileMap(const int *tiles, int width, int height);
	~TileMap(void);

	bool	load(const std::string &tileset);
	void	redraw(void);

private:

	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;

	const int			*tiles;
	int					width;
	int					height;
	sf::VertexArray		m_vertices;
	sf::Texture			m_tileset;
	sf::Vector2u		m_tileSize;
	
};

#endif
