#include "../Endianness/Endianness.h"
#include <stdint.h>

#ifndef _UAPI_LINUX_ELF_H
#define _UAPI_LINUX_ELF_H

// #include <linux/types.h>
#include "elf-em.h"

namespace ELF_format {


	// Elf Data Types for 32/64 bit
	//32 bit
	typedef uint32_t Elf32_Word;
	typedef uint32_t Elf32_Off;
	typedef uint32_t Elf32_Addr;
	typedef uint16_t Elf32_Half;
	typedef int32_t Elf32_Sword;
	typedef uint32_t Elf32_Xword;

	//64 bit
	typedef uint32_t Elf64_Word;
	typedef uint64_t Elf64_Off;
	typedef uint64_t Elf64_Addr;
	typedef uint16_t Elf64_Half;
	typedef uint64_t Elf64_Xword;
	typedef int64_t Elf64_Sxword;   /* Signed long integer. */

	/* These constants are for the segment types stored in the image headers */
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7               /* Thread local storage segment */
#define PT_LOOS    0x60000000      /* OS-specific */
#define PT_HIOS    0x6fffffff      /* OS-specific */
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff
#define PT_GNU_EH_FRAME		0x6474e550

#define PT_GNU_STACK	(PT_LOOS + 0x474e551)

/*
 * Extended Numbering
 *
 * If the real number of program header table entries is larger than
 * or equal to PN_XNUM(0xffff), it is set to sh_info field of the
 * section header at index 0, and PN_XNUM is set to e_phnum
 * field. Otherwise, the section header at index 0 is zero
 * initialized, if it exists.
 *
 * Specifications are available in:
 *
 * - Oracle: Linker and Libraries.
 *   Part No: 817–1984–19, August 2011.
 *   http://docs.oracle.com/cd/E18752_01/pdf/817-1984.pdf
 *
 * - System V ABI AMD64 Architecture Processor Supplement
 *   Draft Version 0.99.4,
 *   January 13, 2010.
 *   http://www.cs.washington.edu/education/courses/cse351/12wi/supp-docs/abi.pdf
 */
#define PN_XNUM 0xffff

 /* These constants define the different elf file types */
#define ET_NONE   0
#define ET_REL    1
#define ET_EXEC   2
#define ET_DYN    3
#define ET_CORE   4
#define ET_LOPROC 0xff00
#define ET_HIPROC 0xffff

/* This is the info that is needed to parse the dynamic section of the file */
#define DT_NULL		0
#define DT_NEEDED	1
#define DT_PLTRELSZ	2
#define DT_PLTGOT	3
#define DT_HASH		4
#define DT_STRTAB	5
#define DT_SYMTAB	6
#define DT_RELA		7
#define DT_RELASZ	8
#define DT_RELAENT	9
#define DT_STRSZ	10
#define DT_SYMENT	11
#define DT_INIT		12
#define DT_FINI		13
#define DT_SONAME	14
#define DT_RPATH 	15
#define DT_SYMBOLIC	16
#define DT_REL	        17
#define DT_RELSZ	18
#define DT_RELENT	19
#define DT_PLTREL	20
#define DT_DEBUG	21
#define DT_TEXTREL	22
#define DT_JMPREL	23
#define DT_ENCODING	32
#define OLD_DT_LOOS	0x60000000
#define DT_LOOS		0x6000000d
#define DT_HIOS		0x6ffff000
#define DT_VALRNGLO	0x6ffffd00
#define DT_VALRNGHI	0x6ffffdff
#define DT_ADDRRNGLO	0x6ffffe00
#define DT_GNU_HASH 0x6ffffef5
#define DT_ADDRRNGHI	0x6ffffeff
#define DT_VERSYM	0x6ffffff0
#define DT_RELACOUNT	0x6ffffff9
#define DT_RELCOUNT	0x6ffffffa
#define DT_FLAGS_1	0x6ffffffb
#define DT_VERDEF	0x6ffffffc
#define	DT_VERDEFNUM	0x6ffffffd
#define DT_VERNEED	0x6ffffffe
#define	DT_VERNEEDNUM	0x6fffffff
#define OLD_DT_HIOS     0x6fffffff
#define DT_LOPROC	0x70000000
#define DT_HIPROC	0x7fffffff

/* This info is needed when parsing the symbol table */
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6

#define ELF_ST_BIND(x)		((x) >> 4)
#define ELF_ST_TYPE(x)		(((unsigned int) x) & 0xf)
#define ELF32_ST_BIND(x)	ELF_ST_BIND(x)
#define ELF32_ST_TYPE(x)	ELF_ST_TYPE(x)
#define ELF64_ST_BIND(x)	ELF_ST_BIND(x)
#define ELF64_ST_TYPE(x)	ELF_ST_TYPE(x)

	template <template<class> class Wrapper> struct dynamic_template {
		Wrapper<Elf32_Sword> d_tag;
		union {
			Wrapper<Elf32_Sword>	d_val;
			Wrapper<Elf32_Addr>	d_ptr;
		} d_un;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(dynamic);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf32_Dyn, dynamic);

	template <template<class> class Wrapper> struct Elf64_Dyn_template {
		Wrapper<Elf64_Sxword> d_tag;		/* entry tag value */
		union {
			Wrapper<Elf64_Xword> d_val;
			Wrapper<Elf64_Addr> d_ptr;
		} d_un;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(Elf64_Dyn);

	/* The following are used with relocations */
#define ELF32_R_SYM(val)		((val) >> 8)
#define ELF32_R_TYPE(val)		((val) & 0xff)
#define ELF32_R_INFO(sym, type)		(((sym) << 8) + ((type) & 0xff))
#define ELF64_R_SYM(i)			((i) >> 32)
#define ELF64_R_TYPE(i)			((i) & 0xffffffff)
#define ELF64_R_INFO(sym,type)		((((Elf64_Xword) (sym)) << 32) + (type))

	template <template<class> class Wrapper> struct elf32_rel_template {
		Wrapper<Elf32_Addr>	r_offset;
		Wrapper<Elf32_Word>	r_info;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf32_rel);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf32_Rel, elf32_rel);

	template <template<class> class Wrapper>  struct elf64_rel_template {
		Wrapper<Elf64_Addr> r_offset;	/* Location at which to apply the action */
		Wrapper<Elf64_Xword> r_info;	/* index and type of relocation */
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf64_rel);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf64_Rel, elf64_rel);

	typedef struct elf32_rela {
		Elf32_Addr	r_offset;
		Elf32_Word	r_info;
		Elf32_Sword	r_addend;
	} Elf32_Rela;

	typedef struct elf64_rela {
		Elf64_Addr r_offset;	/* Location at which to apply the action */
		Elf64_Xword r_info;	/* index and type of relocation */
		Elf64_Sxword r_addend;	/* Constant addend used to compute value */
	} Elf64_Rela;

	template <template<class> class Wrapper> struct elf32_sym_template {
		Wrapper<Elf32_Word>	st_name;
		Wrapper<Elf32_Addr>	st_value;
		Wrapper<Elf32_Word>	st_size;
		Wrapper<unsigned char>	st_info;
		Wrapper<unsigned char>	st_other;
		Wrapper<Elf32_Half>	st_shndx;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf32_sym);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf32_Sym, elf32_sym);

	template <template<class> class Wrapper> struct elf64_sym_template {
		Wrapper<Elf64_Word> st_name;		/* Symbol name, index in string tbl */
		Wrapper<unsigned char>	st_info;	/* Type and binding attributes */
		Wrapper<unsigned char>	st_other;	/* No defined meaning, 0 */
		Wrapper<Elf64_Half> st_shndx;		/* Associated section index */
		Wrapper<Elf64_Addr> st_value;		/* Value of the symbol */
		Wrapper<Elf64_Xword> st_size;		/* Associated symbol size */
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf64_sym);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf64_Sym, elf64_sym);

#define EI_NIDENT	16

	template <template<class> class Wrapper> struct elf32_hdr_template {
		unsigned char	e_ident[EI_NIDENT];
		Wrapper<Elf32_Half>	e_type;
		Wrapper<Elf32_Half>	e_machine;
		Wrapper<Elf32_Word>	e_version;
		Wrapper<Elf32_Addr>	e_entry;  /* Entry point */
		Wrapper<Elf32_Off>	e_phoff;
		Wrapper<Elf32_Off>	e_shoff;
		Wrapper<Elf32_Word>	e_flags;
		Wrapper<Elf32_Half>	e_ehsize;
		Wrapper<Elf32_Half>	e_phentsize;
		Wrapper<Elf32_Half>	e_phnum;
		Wrapper<Elf32_Half>	e_shentsize;
		Wrapper<Elf32_Half>	e_shnum;
		Wrapper<Elf32_Half>	e_shstrndx;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf32_hdr);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf32_Ehdr, elf32_hdr);

	template <template<class> class Wrapper> struct elf64_hdr_template {
		unsigned char	e_ident[EI_NIDENT];	/* ELF "magic number" */
		Wrapper<Elf64_Half> e_type;
		Wrapper<Elf64_Half> e_machine;
		Wrapper<Elf64_Word> e_version;
		Wrapper<Elf64_Addr> e_entry;		/*> entry point virtual address */
		Wrapper<Elf64_Off> e_phoff;		/* Program header table file offset */
		Wrapper<Elf64_Off> e_shoff;		/* Section header table file offset */
		Wrapper<Elf64_Word> e_flags;
		Wrapper<Elf64_Half> e_ehsize;
		Wrapper<Elf64_Half> e_phentsize;
		Wrapper<Elf64_Half> e_phnum;
		Wrapper<Elf64_Half> e_shentsize;
		Wrapper<Elf64_Half> e_shnum;
		Wrapper<Elf64_Half> e_shstrndx;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf64_hdr);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf64_Ehdr, elf64_hdr);

	/* These constants define the permissions on sections in the program
	   header, p_flags. */
#define PF_R		0x4
#define PF_W		0x2
#define PF_X		0x1

	template <template<class> class Wrapper> struct elf32_phdr_template {
		Wrapper<Elf32_Word>	p_type;
		Wrapper<Elf32_Off>	p_offset;
		Wrapper<Elf32_Addr>	p_vaddr;
		Wrapper<Elf32_Addr>	p_paddr;
		Wrapper<Elf32_Word>	p_filesz;
		Wrapper<Elf32_Word>	p_memsz;
		Wrapper<Elf32_Word>	p_flags;
		Wrapper<Elf32_Word>	p_align;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf32_phdr);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf32_Phdr, elf32_phdr);

	template <template<class> class Wrapper> struct elf64_phdr_template {
		Wrapper<Elf64_Word> p_type;
		Wrapper<Elf64_Word> p_flags;
		Wrapper<Elf64_Off> p_offset;		/* Segment file offset */
		Wrapper<Elf64_Addr> p_vaddr;		/* Segment virtual address */
		Wrapper<Elf64_Addr> p_paddr;		/* Segment physical address */
		Wrapper<Elf64_Xword> p_filesz;		/* Segment size in file */
		Wrapper<Elf64_Xword> p_memsz;		/* Segment size in memory */
		Wrapper<Elf64_Xword> p_align;		/* Segment alignment, file & memory */
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf64_phdr);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf64_Phdr, elf64_phdr);

	/* Legal values for sh_type (section type).  */

#define SHT_NULL          0                /* Section header table entry unused */
#define SHT_PROGBITS          1                /* Program data */
#define SHT_SYMTAB          2                /* Symbol table */
#define SHT_STRTAB          3                /* String table */
#define SHT_RELA          4                /* Relocation entries with addends */
#define SHT_HASH          5                /* Symbol hash table */
#define SHT_DYNAMIC          6                /* Dynamic linking information */
#define SHT_NOTE          7                /* Notes */
#define SHT_NOBITS          8                /* Program space with no data (bss) */
#define SHT_REL                  9                /* Relocation entries, no addends */
#define SHT_SHLIB          10                /* Reserved */
#define SHT_DYNSYM          11                /* Dynamic linker symbol table */
#define SHT_INIT_ARRAY          14                /* Array of constructors */
#define SHT_FINI_ARRAY          15                /* Array of destructors */
#define SHT_PREINIT_ARRAY 16                /* Array of pre-constructors */
#define SHT_GROUP          17                /* Section group */
#define SHT_SYMTAB_SHNDX  18                /* Extended section indeces */
#define        SHT_NUM                  19                /* Number of defined types.  */
#define SHT_LOOS          0x60000000        /* Start OS-specific.  */
#define SHT_GNU_ATTRIBUTES 0x6ffffff5        /* Object attributes.  */
#define SHT_GNU_HASH          0x6ffffff6        /* GNU-style hash table.  */
#define SHT_GNU_LIBLIST          0x6ffffff7        /* Prelink library list */
#define SHT_CHECKSUM          0x6ffffff8        /* Checksum for DSO content.  */
#define SHT_LOSUNW          0x6ffffffa        /* Sun-specific low bound.  */
#define SHT_SUNW_move          0x6ffffffa
#define SHT_SUNW_COMDAT   0x6ffffffb
#define SHT_SUNW_syminfo  0x6ffffffc
#define SHT_GNU_verdef          0x6ffffffd        /* Version definition section.  */
#define SHT_GNU_verneed          0x6ffffffe        /* Version needs section.  */
#define SHT_GNU_versym          0x6fffffff        /* Version symbol table.  */
#define SHT_HISUNW          0x6fffffff        /* Sun-specific high bound.  */
#define SHT_HIOS          0x6fffffff        /* End OS-specific type */
#define SHT_LOPROC          0x70000000        /* Start of processor-specific */
#define SHT_HIPROC          0x7fffffff        /* End of processor-specific */
#define SHT_LOUSER          0x80000000        /* Start of application-specific */
#define SHT_HIUSER          0x8fffffff        /* End of application-specific */

/* sh_flags */
#define SHF_WRITE		0x1
#define SHF_ALLOC		0x2
#define SHF_EXECINSTR		0x4
#define SHF_RELA_LIVEPATCH	0x00100000
#define SHF_RO_AFTER_INIT	0x00200000
#define SHF_MASKPROC		0xf0000000

/* special section indexes */
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define SHN_LIVEPATCH	0xff20
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

	template <template<class> class Wrapper> struct elf32_shdr_template {
		Wrapper<Elf32_Word>	sh_name;
		Wrapper<Elf32_Word>	sh_type;
		Wrapper<Elf32_Word>	sh_flags;
		Wrapper<Elf32_Addr>	sh_addr;
		Wrapper<Elf32_Off>	sh_offset;
		Wrapper<Elf32_Word>	sh_size;
		Wrapper<Elf32_Word>	sh_link;
		Wrapper<Elf32_Word>	sh_info;
		Wrapper<Elf32_Word>	sh_addralign;
		Wrapper<Elf32_Word>	sh_entsize;
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf32_shdr);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf32_Shdr, elf32_shdr);

	template <template<class> class Wrapper> struct elf64_shdr_template {
		Wrapper<Elf64_Word> sh_name;		/* Section name, index in string tbl */
		Wrapper<Elf64_Word> sh_type;		/* Type of section */
		Wrapper<Elf64_Xword> sh_flags;		/* Miscellaneous section attributes */
		Wrapper<Elf64_Addr> sh_addr;		/* Section virtual addr at execution */
		Wrapper<Elf64_Off> sh_offset;		/* Section file offset */
		Wrapper<Elf64_Xword> sh_size;		/* Size of section in bytes */
		Wrapper<Elf64_Word> sh_link;		/* Index of another section */
		Wrapper<Elf64_Word> sh_info;		/* Additional section information */
		Wrapper<Elf64_Xword> sh_addralign;	/* Section alignment */
		Wrapper<Elf64_Xword> sh_entsize;	/* Entry size if section holds table */
	};

	DEFINE_ENDIAN_STRUCTURE_DEFAULT(elf64_shdr);
	DEFINE_ENDIAN_STRUCTURE_ALIAS_DEFAULT(Elf64_Shdr, elf64_shdr);

#define	EI_MAG0		0		/* e_ident[] indexes */
#define	EI_MAG1		1
#define	EI_MAG2		2
#define	EI_MAG3		3
#define	EI_CLASS	4
#define	EI_DATA		5
#define	EI_VERSION	6
#define	EI_OSABI	7
#define	EI_PAD		8

#define	ELFMAG0		0x7f		/* EI_MAG */
#define	ELFMAG1		'E'
#define	ELFMAG2		'L'
#define	ELFMAG3		'F'
#define	ELFMAG		"\177ELF"
#define	SELFMAG		4

#define	ELFCLASSNONE	0		/* EI_CLASS */
#define	ELFCLASS32	1
#define	ELFCLASS64	2
#define	ELFCLASSNUM	3

#define ELFDATANONE	0		/* e_ident[EI_DATA] */
#define ELFDATA2LSB	1
#define ELFDATA2MSB	2

#define EV_NONE		0		/* e_version, EI_VERSION */
#define EV_CURRENT	1
#define EV_NUM		2

#define ELFOSABI_NONE	0
#define ELFOSABI_LINUX	3

#ifndef ELF_OSABI
#define ELF_OSABI ELFOSABI_NONE
#endif

	/*
	 * Notes used in ET_CORE. Architectures export some of the arch register sets
	 * using the corresponding note types via the PTRACE_GETREGSET and
	 * PTRACE_SETREGSET requests.
	 */
#define NT_PRSTATUS	1
#define NT_PRFPREG	2
#define NT_PRPSINFO	3
#define NT_TASKSTRUCT	4
#define NT_AUXV		6
	 /*
	  * Note to userspace developers: size of NT_SIGINFO note may increase
	  * in the future to accomodate more fields, don't assume it is fixed!
	  */
#define NT_SIGINFO      0x53494749
#define NT_FILE         0x46494c45
#define NT_PRXFPREG     0x46e62b7f      /* copied from gdb5.1/include/elf/common.h */
#define NT_PPC_VMX	0x100		/* PowerPC Altivec/VMX registers */
#define NT_PPC_SPE	0x101		/* PowerPC SPE/EVR registers */
#define NT_PPC_VSX	0x102		/* PowerPC VSX registers */
#define NT_PPC_TAR	0x103		/* Target Address Register */
#define NT_PPC_PPR	0x104		/* Program Priority Register */
#define NT_PPC_DSCR	0x105		/* Data Stream Control Register */
#define NT_PPC_EBB	0x106		/* Event Based Branch Registers */
#define NT_PPC_PMU	0x107		/* Performance Monitor Registers */
#define NT_PPC_TM_CGPR	0x108		/* TM checkpointed GPR Registers */
#define NT_PPC_TM_CFPR	0x109		/* TM checkpointed FPR Registers */
#define NT_PPC_TM_CVMX	0x10a		/* TM checkpointed VMX Registers */
#define NT_PPC_TM_CVSX	0x10b		/* TM checkpointed VSX Registers */
#define NT_PPC_TM_SPR	0x10c		/* TM Special Purpose Registers */
#define NT_PPC_TM_CTAR	0x10d		/* TM checkpointed Target Address Register */
#define NT_PPC_TM_CPPR	0x10e		/* TM checkpointed Program Priority Register */
#define NT_PPC_TM_CDSCR	0x10f		/* TM checkpointed Data Stream Control Register */
#define NT_386_TLS	0x200		/* i386 TLS slots (struct user_desc) */
#define NT_386_IOPERM	0x201		/* x86 io permission bitmap (1=deny) */
#define NT_X86_XSTATE	0x202		/* x86 extended state using xsave */
#define NT_S390_HIGH_GPRS	0x300	/* s390 upper register halves */
#define NT_S390_TIMER	0x301		/* s390 timer register */
#define NT_S390_TODCMP	0x302		/* s390 TOD clock comparator register */
#define NT_S390_TODPREG	0x303		/* s390 TOD programmable register */
#define NT_S390_CTRS	0x304		/* s390 control registers */
#define NT_S390_PREFIX	0x305		/* s390 prefix register */
#define NT_S390_LAST_BREAK	0x306	/* s390 breaking event address */
#define NT_S390_SYSTEM_CALL	0x307	/* s390 system call restart data */
#define NT_S390_TDB	0x308		/* s390 transaction diagnostic block */
#define NT_S390_VXRS_LOW	0x309	/* s390 vector registers 0-15 upper half */
#define NT_S390_VXRS_HIGH	0x30a	/* s390 vector registers 16-31 */
#define NT_ARM_VFP	0x400		/* ARM VFP/NEON registers */
#define NT_ARM_TLS	0x401		/* ARM TLS register */
#define NT_ARM_HW_BREAK	0x402		/* ARM hardware breakpoint registers */
#define NT_ARM_HW_WATCH	0x403		/* ARM hardware watchpoint registers */
#define NT_ARM_SYSTEM_CALL	0x404	/* ARM system call number */
#define NT_METAG_CBUF	0x500		/* Metag catch buffer registers */
#define NT_METAG_RPIPE	0x501		/* Metag read pipeline state */
#define NT_METAG_TLS	0x502		/* Metag TLS pointer */


	  /* Note header in a PT_NOTE section */
	typedef struct elf32_note {
		Elf32_Word	n_namesz;	/* Name size */
		Elf32_Word	n_descsz;	/* Content size */
		Elf32_Word	n_type;		/* Content type */
	} Elf32_Nhdr;

	/* Note header in a PT_NOTE section */
	typedef struct elf64_note {
		Elf64_Word n_namesz;	/* Name size */
		Elf64_Word n_descsz;	/* Content size */
		Elf64_Word n_type;	/* Content type */
	} Elf64_Nhdr;
}

#endif /* _UAPI_LINUX_ELF_H */
