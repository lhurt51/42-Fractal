/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_maps1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:37:43 by lhurt             #+#    #+#             */
/*   Updated: 2017/01/23 17:37:45 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		*map_seashoresinv(void)
{
	static int seashores_center[64] = {
		0xffff7d, 0xfbff7d, 0xf7ff7d, 0xf2ff7d,
		0xeeff7d, 0xebff7d, 0xe7ff7d, 0xe3ff7e,
		0xdfff7e, 0xdbff7e, 0xd7ff7e, 0xd3ff7e,
		0xcfff7e, 0xcbff7e, 0xc7ff7e, 0xc3ff7e,
		0xbfff7e, 0xbbff7e, 0xb7ff7e, 0xb3ff7e,
		0xafff7e, 0xabff7e, 0xa7ff7e, 0xa3ff7e,
		0x9fff7e, 0x9bff7e, 0x97ff7e, 0x93ff7e,
		0x8fff7f, 0x8aff7f, 0x86ff7f, 0x83ff7f,
		0x7efe7f, 0x7afa7f, 0x76f67f, 0x73f27f,
		0x6fee7f, 0x6bea7f, 0x66e67f, 0x62e27f,
		0x5ede7f, 0x5bda7f, 0x57d67f, 0x53d27f,
		0x4fce7f, 0x4bca7f, 0x46c67f, 0x42c27f,
		0x3fbe7f, 0x3bba7f, 0x36b67f, 0x33b27f,
		0x2fae7f, 0x2aa97f, 0x27a57f, 0x22a17f,
		0x1f9d7f, 0x1b997f, 0x16957f, 0x12917f,
		0xe8d7f, 0xb897f, 0x6857f, 0x2817f};

	return (seashores_center);
}

int		*map_redblue(void)
{
	static int red_to_blue[64] = {
		0x5f0000, 0x650000, 0x6b0000, 0x720000,
		0x780000, 0x7e0000, 0x840000, 0x8a0000,
		0x900000, 0x960000, 0x9d0000, 0xa30000,
		0xa90000, 0xaf0000, 0xb50000, 0xbb0000,
		0xc10101, 0xc51111, 0xc92121, 0xcd3131,
		0xd14141, 0xd55151, 0xd96161, 0xdd7171,
		0xe08181, 0xe49191, 0xe8a1a1, 0xecb1b1,
		0xf0c1c1, 0xf4d1d1, 0xf8e1e1, 0xfcf1f1,
		0xfdfdff, 0xededfb, 0xddddf7, 0xcdcdf3,
		0xbdbdef, 0xadadec, 0x9d9de8, 0x8d8de4,
		0x7d7de0, 0x6d6ddc, 0x5d5dd9, 0x4d4dd5,
		0x3d3dd1, 0x2d2dcd, 0x1d1dca, 0xd0dc6,
		0xc2, 0xbb, 0xb5, 0xaf,
		0xa9, 0xa2, 0x9c, 0x96,
		0x90, 0x89, 0x83, 0x7d,
		0x77, 0x70, 0x6a, 0x64};

	return (red_to_blue);
}

int		*map_rainbow(void)
{
	static int rainbow[64] = {
		0xFF0005, 0xFE1100, 0xFE2900, 0xFE4100,
		0xFD5800, 0xFD7000, 0xFD8700, 0xFD9F00,
		0xFCB600, 0xFCCE00, 0xFCE500, 0xFBFB00,
		0xE3FB00, 0xCBFB00, 0xB4FB00, 0x9CFA00,
		0x85FA00, 0x6DFA00, 0x56F900, 0x3FF900,
		0x27F900, 0x10F900, 0x00F808, 0x00F81F,
		0x00F836, 0x00F74D, 0x00F764, 0x00F77B,
		0x00F791, 0x00F6A8, 0x00F6BF, 0x01F6D6,
		0x01F5EC, 0x01E7F5, 0x01D0F5, 0x01B9F5,
		0x01A2F4, 0x018CF4, 0x0175F4, 0x015EF3,
		0x0147F3, 0x0131F3, 0x011AF3, 0x0104F2,
		0x1501F2, 0x2B01F2, 0x4201F1, 0x5801F1,
		0x6E01F1, 0x8501F0, 0x9B01F0, 0xB101F0,
		0xC701F0, 0xDD01EF, 0xEF01EB, 0xEF01D5,
		0xEF01BF, 0xEE01A8, 0xEE0192, 0xEE017C,
		0xED0166, 0xED0150, 0xED0139, 0xED0123};

	return (rainbow);
}

int		*map_kryptonite(void)
{
	static int kryptonite[64] = {
		0xffffff, 0xfffff7, 0xffffef, 0xffffe7,
		0xffffdf, 0xffffd7, 0xffffcf, 0xffffc7,
		0xffffbf, 0xffffb7, 0xffffaf, 0xffffa8,
		0xffffa0, 0xffff98, 0xffff90, 0xffff88,
		0xffff80, 0xf7ff78, 0xeeff70, 0xe7ff68,
		0xdfff60, 0xd7ff58, 0xcfff4f, 0xc7ff47,
		0xbfff3f, 0xb7ff37, 0xafff2f, 0xa7ff27,
		0x9fff1f, 0x97ff17, 0x8fff0f, 0x86ff07,
		0x7efe00, 0x76f600, 0x6fee00, 0x66e600,
		0x5edf00, 0x57d700, 0x4fcf00, 0x46c700,
		0x3fbf00, 0x36b700, 0x2faf00, 0x27a800,
		0x1fa000, 0x169800, 0xe9000, 0x68800,
		0x8000, 0x7800, 0x7000, 0x6800,
		0x6000, 0x5800, 0x4f00, 0x4700,
		0x3f00, 0x3700, 0x2f00, 0x2700,
		0x1f00, 0x1600, 0xe00, 0x600};

	return (kryptonite);
}

int		*extra_maps(int i)
{
	if (i == 4)
		return (map_seashoresinv());
	else if (i == 5)
		return (map_redblue());
	else if (i == 6)
		return (map_rainbow());
	else if (i == 7)
		return (map_kryptonite());
	else
		return (extra_maps1(i));
}
