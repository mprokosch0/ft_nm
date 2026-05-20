#include "ft_nm.h"

void	ui16_byte_swap(uint16_t *addr)
{
	uint8_t b0, b1;

	b0 = (*addr) >> 8;
	b1 = (*addr);

	*addr = (uint16_t)b1 << 8 | b0;
}

void	ui32_byte_swap(uint32_t *addr)
{
	uint8_t b0, b1, b2, b3;

	b0 = (*addr) >> 24;
	b1 = (*addr) >> 16;
	b2 = (*addr) >> 8;
	b3 = (*addr);

	*addr = (uint32_t)b3 << 24 | (uint32_t)b2 << 16 | (uint32_t)b1 << 8 | b0;
}

void	ui64_byte_swap(uint64_t *addr)
{
	uint8_t b0, b1, b2, b3, b4, b5, b6, b7;

	b0 = (*addr) >> 56;
	b1 = (*addr) >> 48;
	b2 = (*addr) >> 40;
	b3 = (*addr) >> 32;
	b4 = (*addr) >> 24;
	b5 = (*addr) >> 16;
	b6 = (*addr) >> 8;
	b7 = (*addr);

	*addr = (uint64_t)b7 << 56 | (uint64_t)b6 << 48 | (uint64_t)b5 << 40 | (uint64_t)b4 << 32
			| (uint64_t)b3 << 24 | (uint64_t)b2 << 16 | (uint64_t)b1 << 8 | b0;
}

void	print_hex_32(uint32_t nb)
{
	uint32_t tmp = nb;
	size_t count = 0;

	while (tmp)
	{
		tmp /= 16;
		count++;
	}
	for (size_t i = 0; i < 8 - count; i++)
		ft_dprintf(1, "0");
	if (nb)
		ft_dprintf(1, "%x", nb);
	ft_dprintf(1, " ");
}

void	print_hex_64(uint64_t nb)
{
	uint64_t tmp = nb;
	size_t count = 0;

	while (tmp)
	{
		tmp /= 16;
		count++;
	}
	for (size_t i = 0; i < 16 - count; i++)
		ft_dprintf(1, "0");
	if (nb)
		ft_dprintf(1, "%x", nb);
	ft_dprintf(1, " ");
}


bool	unmap(void *addr, size_t lenght, const char *file_name)
{
	ft_dprintf(2, "ft_nm: %s: file format not recognized\n", file_name);
	if (munmap(addr, lenght))
		ft_dprintf(2, "ft_nm: %sfiles[i]: Error: munmap failed\n", file_name);
	return false;
}