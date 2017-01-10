/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:08:13 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/14 16:08:22 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft/libft.h"

# define W_WIDTH 1920
# define W_HEIGHT 1080
# define W_XORIGIN W_WIDTH / 2
# define W_YORIGIN W_HEIGHT / 2
# define ZOOM_SPEED 2

typedef struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bits;
	int				size_line;
	int				endian;
	double			scale;
	double			x_offset;
	double			y_offset;
}					t_mlx;

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

static int fire[64] = {
	0xffffff, 0xfffff7, 0xffffef, 0xffffe7,
	0xffffdf, 0xffffd7, 0xffffcf, 0xffffc7,
	0xffffbf, 0xffffb7, 0xffffaf, 0xffffa8,
	0xffffa0, 0xffff98, 0xffff90, 0xffff88,
	0xffff80, 0xfff778, 0xffee70, 0xffe768,
	0xffdf60, 0xffd758, 0xffcf4f, 0xffc747,
	0xffbf3f, 0xffb737, 0xffaf2f, 0xffa727,
	0xff9f1f, 0xff9717, 0xff8f0f, 0xff8607,
	0xfe7e00, 0xf67600, 0xee6f00, 0xe66600,
	0xdf5e00, 0xd75700, 0xcf4f00, 0xc74600,
	0xbf3f00, 0xb73600, 0xaf2f00, 0xa82700,
	0xa01f00, 0x981600, 0x900e00, 0x880600,
	0x800000, 0x780000, 0x700000, 0x680000,
	0x600000, 0x580000, 0x4f0000, 0x470000,
	0x3f0000, 0x370000, 0x2f0000, 0x270000,
	0x1f0000, 0x160000, 0xe0000, 0x60000};

static int fire_center[64] = {
	0xffff80, 0xfffb7c, 0xfff778, 0xfff274,
	0xffee70, 0xffeb6c, 0xffe768, 0xffe364,
	0xffdf60, 0xffdb5c, 0xffd758, 0xffd354,
	0xffcf4f, 0xffcb4b, 0xffc747, 0xffc343,
	0xffbf3f, 0xffbb3b, 0xffb737, 0xffb333,
	0xffaf2f, 0xffab2b, 0xffa727, 0xffa323,
	0xff9f1f, 0xff9b1b, 0xff9717, 0xff9313,
	0xff8f0f, 0xff8a0b, 0xff8607, 0xff8303,
	0xfe7e00, 0xfa7a00, 0xf67600, 0xf27300,
	0xee6f00, 0xea6b00, 0xe66600, 0xe36200,
	0xdf5e00, 0xdb5b00, 0xd75700, 0xd35300,
	0xcf4f00, 0xcb4b00, 0xc74600, 0xc34200,
	0xbf3f00, 0xbb3b00, 0xb73600, 0xb33300,
	0xaf2f00, 0xac2a00, 0xa82700, 0xa42200,
	0xa01f00, 0x9c1b00, 0x981600, 0x941200,
	0x900e00, 0x8c0b00, 0x880600, 0x840200};

static int ice[64] = {
	0xffffff, 0xf7ffff, 0xefffff, 0xe7ffff,
	0xdfffff, 0xd7ffff, 0xcfffff, 0xc7ffff,
	0xbfffff, 0xb7ffff, 0xafffff, 0xa8ffff,
	0xa0ffff, 0x98ffff, 0x90ffff, 0x88ffff,
	0x80ffff, 0x78f7ff, 0x70eeff, 0x68e7ff,
	0x60dfff, 0x58d7ff, 0x4fcfff, 0x47c7ff,
	0x3fbfff, 0x37b7ff, 0x2fafff, 0x27a7ff,
	0x1f9fff, 0x1797ff, 0xf8fff, 0x786ff,
	0x7efe, 0x76f6, 0x6fee, 0x66e6,
	0x5edf, 0x57d7, 0x4fcf, 0x46c7,
	0x3fbf, 0x36b7, 0x2faf, 0x27a8,
	0x1fa0, 0x1698, 0xe90, 0x688,
	0x80, 0x78, 0x70, 0x68,
	0x60, 0x58, 0x4f, 0x47,
	0x3f, 0x37, 0x2f, 0x27,
	0x1f, 0x16, 0xe, 0x6};

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

static int kryptonite_center[64] = {
	0xffff80, 0xfbff7c, 0xf7ff78, 0xf2ff74,
	0xeeff70, 0xebff6c, 0xe7ff68, 0xe3ff64,
	0xdfff60, 0xdbff5c, 0xd7ff58, 0xd3ff54,
	0xcfff4f, 0xcbff4b, 0xc7ff47, 0xc3ff43,
	0xbfff3f, 0xbbff3b, 0xb7ff37, 0xb3ff33,
	0xafff2f, 0xabff2b, 0xa7ff27, 0xa3ff23,
	0x9fff1f, 0x9bff1b, 0x97ff17, 0x93ff13,
	0x8fff0f, 0x8aff0b, 0x86ff07, 0x83ff03,
	0x7efe00, 0x7afa00, 0x76f600, 0x73f200,
	0x6fee00, 0x6bea00, 0x66e600, 0x62e300,
	0x5edf00, 0x5bdb00, 0x57d700, 0x53d300,
	0x4fcf00, 0x4bcb00, 0x46c700, 0x42c300,
	0x3fbf00, 0x3bbb00, 0x36b700, 0x33b300,
	0x2faf00, 0x2aac00, 0x27a800, 0x22a400,
	0x1fa000, 0x1b9c00, 0x169800, 0x129400,
	0xe9000, 0xb8c00, 0x68800, 0x28400};

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

#endif