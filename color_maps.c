/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 16:50:14 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/12 16:50:31 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		*map_dawn(void)
{
	static int dawn[64] = {
		0xffffc3, 0xffffbe, 0xffffba, 0xffffb6,
		0xffffb1, 0xffffad, 0xffffa9, 0xffffa4,
		0xffffa0, 0xffff9b, 0xffff97, 0xffff93,
		0xffff8e, 0xffff8a, 0xffff86, 0xffff81,
		0xffff7d, 0xfff77d, 0xffee7d, 0xffe77d,
		0xffdf7e, 0xffd77e, 0xffcf7e, 0xffc77e,
		0xffbf7e, 0xffb77e, 0xffaf7e, 0xffa77e,
		0xff9f7e, 0xff977e, 0xff8f7f, 0xff867f,
		0xfe7e7f, 0xf6767f, 0xee6f7f, 0xe6667f,
		0xde5e7f, 0xd6577f, 0xce4f7f, 0xc6467f,
		0xbe3f7f, 0xb6367f, 0xae2f7f, 0xa5277f,
		0x9d1f7f, 0x95167f, 0x8d0e7f, 0x85067f,
		0x7d007f, 0x75007f, 0x6d007f, 0x65007f,
		0x5d007f, 0x55007e, 0x4e007e, 0x46007e,
		0x3e007e, 0x36007e, 0x2e007e, 0x26007e,
		0x1e007e, 0x16007e, 0xe007e, 0x6007e};

	return (dawn);
}

int		*map_dawninv(void)
{
	static int dawn_center[64] = {
		0xffff7d, 0xfffb7d, 0xfff77d, 0xfff27d,
		0xffee7d, 0xffeb7d, 0xffe77d, 0xffe37e,
		0xffdf7e, 0xffdb7e, 0xffd77e, 0xffd37e,
		0xffcf7e, 0xffcb7e, 0xffc77e, 0xffc37e,
		0xffbf7e, 0xffbb7e, 0xffb77e, 0xffb37e,
		0xffaf7e, 0xffab7e, 0xffa77e, 0xffa37e,
		0xff9f7e, 0xff9b7e, 0xff977e, 0xff937e,
		0xff8f7f, 0xff8a7f, 0xff867f, 0xff837f,
		0xfe7e7f, 0xfa7a7f, 0xf6767f, 0xf2737f,
		0xee6f7f, 0xea6b7f, 0xe6667f, 0xe2627f,
		0xde5e7f, 0xda5b7f, 0xd6577f, 0xd2537f,
		0xce4f7f, 0xca4b7f, 0xc6467f, 0xc2427f,
		0xbe3f7f, 0xba3b7f, 0xb6367f, 0xb2337f,
		0xae2f7f, 0xa92a7f, 0xa5277f, 0xa1227f,
		0x9d1f7f, 0x991b7f, 0x95167f, 0x91127f,
		0x8d0e7f, 0x890b7f, 0x85067f, 0x81027f};

	return (dawn_center);
}

int		*map_dusk(void)
{
	static int dusk[64] = {
		0xffffff, 0xfff7ff, 0xffefff, 0xffe7ff,
		0xffdfff, 0xffd7ff, 0xffcfff, 0xffc7ff,
		0xffbfff, 0xffb7ff, 0xffafff, 0xffa8ff,
		0xffa0ff, 0xff98ff, 0xff90ff, 0xff88ff,
		0xff80ff, 0xf778ff, 0xee70ff, 0xe768ff,
		0xdf60ff, 0xd758ff, 0xcf4fff, 0xc747ff,
		0xbf3fff, 0xb737ff, 0xaf2fff, 0xa727ff,
		0x9f1fff, 0x9717ff, 0x8f0fff, 0x8607ff,
		0x7e00fe, 0x7600f6, 0x6f00ee, 0x6600e6,
		0x5e00df, 0x5700d7, 0x4f00cf, 0x4600c7,
		0x3f00bf, 0x3600b7, 0x2f00af, 0x2700a8,
		0x1f00a0, 0x160098, 0xe0090, 0x60088,
		0x80, 0x78, 0x70, 0x68,
		0x60, 0x58, 0x4f, 0x47,
		0x3f, 0x37, 0x2f, 0x27,
		0x1f, 0x16, 0xe, 0x6};

	return (dusk);
}

int		*map_seashores(void)
{
	static int seashores[64] = {
		0xffffc3, 0xffffbe, 0xffffba, 0xffffb6,
		0xffffb1, 0xffffad, 0xffffa9, 0xffffa4,
		0xffffa0, 0xffff9b, 0xffff97, 0xffff93,
		0xffff8e, 0xffff8a, 0xffff86, 0xffff81,
		0xffff7d, 0xf7ff7d, 0xeeff7d, 0xe7ff7d,
		0xdfff7e, 0xd7ff7e, 0xcfff7e, 0xc7ff7e,
		0xbfff7e, 0xb7ff7e, 0xafff7e, 0xa7ff7e,
		0x9fff7e, 0x97ff7e, 0x8fff7f, 0x86ff7f,
		0x7efe7f, 0x76f67f, 0x6fee7f, 0x66e67f,
		0x5ede7f, 0x57d67f, 0x4fce7f, 0x46c67f,
		0x3fbe7f, 0x36b67f, 0x2fae7f, 0x27a57f,
		0x1f9d7f, 0x16957f, 0xe8d7f, 0x6857f,
		0x7d7f, 0x757f, 0x6d7f, 0x657f,
		0x5d7f, 0x557e, 0x4e7e, 0x467e,
		0x3e7e, 0x367e, 0x2e7e, 0x267e,
		0x1e7e, 0x167e, 0xe7e, 0x67e};

	return (seashores);
}

int		*return_map(int i)
{
	if (i == 0)
		return (map_dawn());
	else if (i == 1)
		return (map_dawninv());
	else if (i == 2)
		return (map_dusk());
	else if (i == 3)
		return (map_seashores());
	else
		return (extra_maps(i));
}
