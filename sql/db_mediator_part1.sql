--1. t_ad - administrative division
CREATE TABLE t_ad
(
	i_ad INTEGER NOT NULL,					--id округа
	x_ad VARCHAR(64) NOT NULL,				--название округа
	x_ad_abbreviation VARCHAR(16) NOT NULL	--аббревиатура округа
);
CREATE UNIQUE INDEX idx_ad ON t_ad (i_ad ASC);
CREATE UNIQUE INDEX idx_xad ON t_ad (x_ad ASC);

--2. t_mr - municipal region 
CREATE TABLE t_mr
(
	i_mr INTEGER NOT NULL,					--id района
	i_ad INTEGER NOT NULL,					--id округа
	x_mr VARCHAR(128) NOT NULL				--название района
);
CREATE UNIQUE INDEX idx_mr ON t_mr (i_mr ASC);
CREATE UNIQUE INDEX idx_admr ON t_mr (i_ad ASC, i_mr ASC);
CREATE UNIQUE INDEX idx_xmr ON t_mr (x_mr ASC);
