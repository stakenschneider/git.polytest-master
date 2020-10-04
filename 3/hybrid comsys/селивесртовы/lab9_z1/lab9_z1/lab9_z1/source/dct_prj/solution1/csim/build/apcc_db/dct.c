/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;

/* External Global Variable Declarations */

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void dct_1d(signed short *llvm_cbe_src, signed short *llvm_cbe_dst);
void dct_2d(signed short (*llvm_cbe_in_block)[8], signed short (*llvm_cbe_out_block)[8]);
void read_data(signed short *llvm_cbe_input, signed short (*llvm_cbe_buf)[8]);
void write_data(signed short (*llvm_cbe_buf)[8], signed short *llvm_cbe_output);
void dct(signed short *llvm_cbe_input, signed short *llvm_cbe_output);


/* Global Variable Definitions and Initialization */
static signed short aesl_internal_dct_1d_OC_dct_coeff_table[8][8] = { { ((unsigned short )8192), ((unsigned short )8192), ((unsigned short )8192), ((unsigned short )8192), ((unsigned short )8192), ((unsigned short )8192), ((unsigned short )8192), ((unsigned short )8192) }, { ((unsigned short )11363), ((unsigned short )9633), ((unsigned short )6436), ((unsigned short )2260), ((unsigned short )-2260), ((unsigned short )-6436), ((unsigned short )-9632), ((unsigned short )-11362) }, { ((unsigned short )10703), ((unsigned short )4433), ((unsigned short )-4433), ((unsigned short )-10703), ((unsigned short )-10703), ((unsigned short )-4433), ((unsigned short )4433), ((unsigned short )10703) }, { ((unsigned short )9633), ((unsigned short )-2260), ((unsigned short )-11362), ((unsigned short )-6436), ((unsigned short )6436), ((unsigned short )11363), ((unsigned short )2260), ((unsigned short )-9632) }, { ((unsigned short )8192), ((unsigned short )-8192), ((unsigned short )-8192), ((unsigned short )8192), ((unsigned short )8192), ((unsigned short )-8191), ((unsigned short )-8191), ((unsigned short )8192) }, { ((unsigned short )6436), ((unsigned short )-11362), ((unsigned short )2260), ((unsigned short )9633), ((unsigned short )-9632), ((unsigned short )-2260), ((unsigned short )11363), ((unsigned short )-6436) }, { ((unsigned short )4433), ((unsigned short )-10703), ((unsigned short )10703), ((unsigned short )-4433), ((unsigned short )-4433), ((unsigned short )10703), ((unsigned short )-10703), ((unsigned short )4433) }, { ((unsigned short )2260), ((unsigned short )-6436), ((unsigned short )9633), ((unsigned short )-11362), ((unsigned short )11363), ((unsigned short )-9632), ((unsigned short )6436), ((unsigned short )-2260) } };


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

void dct_1d(signed short *llvm_cbe_src, signed short *llvm_cbe_dst) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  unsigned long long llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  signed short *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  unsigned short llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  unsigned short llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  unsigned int llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  unsigned int llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  signed short *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  unsigned short llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  unsigned int llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  signed short *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  unsigned short llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  unsigned int llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  unsigned int llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  signed short *llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  unsigned short llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  signed short *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  unsigned short llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  unsigned int llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  unsigned int llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  signed short *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  unsigned short llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  unsigned int llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  signed short *llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  unsigned short llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  signed short *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned short llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  unsigned int llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  signed short *llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  unsigned short llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  signed short *llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  unsigned short llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  signed short *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  unsigned short llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  unsigned int llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  unsigned int llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  signed short *llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  unsigned short llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  unsigned int llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  signed short *llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  unsigned short llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  unsigned int llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  signed short *llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  unsigned short llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  unsigned int llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  signed short *llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  unsigned short llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  unsigned int llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  unsigned int llvm_cbe_tmp__63;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  unsigned int llvm_cbe_tmp__64;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  unsigned int llvm_cbe_tmp__65;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  unsigned short llvm_cbe_tmp__66;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  signed short *llvm_cbe_tmp__67;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  unsigned int llvm_cbe_tmp__68;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @dct_1d\n");
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ 0, %%0 ], [ %%68, %%.preheader  for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__68);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = zext i32 %%storemerge1 to i64, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_11_count);
  llvm_cbe_tmp__1 = (unsigned long long )((unsigned long long )(unsigned int )llvm_cbe_storemerge1&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__1);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 0, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_12_count);
  llvm_cbe_tmp__2 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )0ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i16* %%2, align 16, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_13_count);
  llvm_cbe_tmp__3 = (unsigned short )*llvm_cbe_tmp__2;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = sext i16 %%3 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_14_count);
  llvm_cbe_tmp__4 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load i16* %%src, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_17_count);
  llvm_cbe_tmp__5 = (unsigned short )*llvm_cbe_src;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sext i16 %%5 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_18_count);
  llvm_cbe_tmp__6 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = mul nsw i32 %%6, %%4, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_19_count);
  llvm_cbe_tmp__7 = (unsigned int )((unsigned int )(llvm_cbe_tmp__6&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__4&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__7&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 1, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__8 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )1ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i16* %%8, align 2, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__9 = (unsigned short )*llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sext i16 %%9 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__10 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds i16* %%src, i64 1, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__11 = (signed short *)(&llvm_cbe_src[(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load i16* %%11, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__12 = (unsigned short )*llvm_cbe_tmp__11;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sext i16 %%12 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__13 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = mul nsw i32 %%13, %%10, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__14 = (unsigned int )((unsigned int )(llvm_cbe_tmp__13&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__10&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__14&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = add nsw i32 %%14, %%7, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__15 = (unsigned int )((unsigned int )(llvm_cbe_tmp__14&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__7&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__15&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 2, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__16 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )2ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load i16* %%16, align 4, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__17 = (unsigned short )*llvm_cbe_tmp__16;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = sext i16 %%17 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__18 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds i16* %%src, i64 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__19 = (signed short *)(&llvm_cbe_src[(((signed long long )2ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = load i16* %%19, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_52_count);
  llvm_cbe_tmp__20 = (unsigned short )*llvm_cbe_tmp__19;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = sext i16 %%20 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_53_count);
  llvm_cbe_tmp__21 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = mul nsw i32 %%21, %%18, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_54_count);
  llvm_cbe_tmp__22 = (unsigned int )((unsigned int )(llvm_cbe_tmp__21&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__18&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__22&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = add nsw i32 %%22, %%15, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_55_count);
  llvm_cbe_tmp__23 = (unsigned int )((unsigned int )(llvm_cbe_tmp__22&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__15&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__23&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 3, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_64_count);
  llvm_cbe_tmp__24 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )3ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = load i16* %%24, align 2, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_65_count);
  llvm_cbe_tmp__25 = (unsigned short )*llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = sext i16 %%25 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__26 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__25);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = getelementptr inbounds i16* %%src, i64 3, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_69_count);
  llvm_cbe_tmp__27 = (signed short *)(&llvm_cbe_src[(((signed long long )3ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load i16* %%27, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__28 = (unsigned short )*llvm_cbe_tmp__27;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = sext i16 %%28 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__29 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = mul nsw i32 %%29, %%26, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__30 = (unsigned int )((unsigned int )(llvm_cbe_tmp__29&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__26&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__30&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = add nsw i32 %%30, %%23, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(llvm_cbe_tmp__30&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__23&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__31&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 4, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__32 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )4ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i16* %%32, align 8, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__33 = (unsigned short )*llvm_cbe_tmp__32;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = sext i16 %%33 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__34 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = getelementptr inbounds i16* %%src, i64 4, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__35 = (signed short *)(&llvm_cbe_src[(((signed long long )4ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = load i16* %%35, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__36 = (unsigned short )*llvm_cbe_tmp__35;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = sext i16 %%36 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__37 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__37);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = mul nsw i32 %%37, %%34, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__38 = (unsigned int )((unsigned int )(llvm_cbe_tmp__37&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__34&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__38&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = add nsw i32 %%38, %%31, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_91_count);
  llvm_cbe_tmp__39 = (unsigned int )((unsigned int )(llvm_cbe_tmp__38&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__31&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__39&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 5, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__40 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )5ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = load i16* %%40, align 2, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__41 = (unsigned short )*llvm_cbe_tmp__40;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = sext i16 %%41 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__42 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = getelementptr inbounds i16* %%src, i64 5, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__43 = (signed short *)(&llvm_cbe_src[(((signed long long )5ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = load i16* %%43, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_106_count);
  llvm_cbe_tmp__44 = (unsigned short )*llvm_cbe_tmp__43;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = sext i16 %%44 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__45 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__45);
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = mul nsw i32 %%45, %%42, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__46 = (unsigned int )((unsigned int )(llvm_cbe_tmp__45&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__42&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__46&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = add nsw i32 %%46, %%39, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__47 = (unsigned int )((unsigned int )(llvm_cbe_tmp__46&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__39&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__47&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 6, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__48 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )6ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = load i16* %%48, align 4, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__49 = (unsigned short )*llvm_cbe_tmp__48;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = sext i16 %%49 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__50 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__49);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__50);
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = getelementptr inbounds i16* %%src, i64 6, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_123_count);
  llvm_cbe_tmp__51 = (signed short *)(&llvm_cbe_src[(((signed long long )6ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = load i16* %%51, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__52 = (unsigned short )*llvm_cbe_tmp__51;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = sext i16 %%52 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__53 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = mul nsw i32 %%53, %%50, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(llvm_cbe_tmp__53&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__50&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__54&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = add nsw i32 %%54, %%47, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__55 = (unsigned int )((unsigned int )(llvm_cbe_tmp__54&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__47&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__55&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = getelementptr inbounds [8 x [8 x i16]]* @aesl_internal_dct_1d.dct_coeff_table, i64 0, i64 %%1, i64 7, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__56 = (signed short *)(&aesl_internal_dct_1d_OC_dct_coeff_table[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )llvm_cbe_tmp__1) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )7ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'aesl_internal_dct_1d.dct_coeff_table' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = load i16* %%56, align 2, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__57 = (unsigned short )*llvm_cbe_tmp__56;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = sext i16 %%57 to i32, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__58 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__58);
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = getelementptr inbounds i16* %%src, i64 7, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__59 = (signed short *)(&llvm_cbe_src[(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = load i16* %%59, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__60 = (unsigned short )*llvm_cbe_tmp__59;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = sext i16 %%60 to i32, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__61 = (unsigned int )((signed int )(signed short )llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__61);
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = mul nsw i32 %%61, %%58, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_144_count);
  llvm_cbe_tmp__62 = (unsigned int )((unsigned int )(llvm_cbe_tmp__61&4294967295ull)) * ((unsigned int )(llvm_cbe_tmp__58&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__62&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = add nsw i32 %%62, %%55, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_145_count);
  llvm_cbe_tmp__63 = (unsigned int )((unsigned int )(llvm_cbe_tmp__62&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__55&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__63&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = add nsw i32 %%63, 4096, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_154_count);
  llvm_cbe_tmp__64 = (unsigned int )((unsigned int )(llvm_cbe_tmp__63&4294967295ull)) + ((unsigned int )(4096u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__64&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = lshr i32 %%64, 13, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_155_count);
  llvm_cbe_tmp__65 = (unsigned int )((unsigned int )(((unsigned int )(llvm_cbe_tmp__64&4294967295ull)) >> ((unsigned int )(13u&4294967295ull))));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__65&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = trunc i32 %%65 to i16, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_156_count);
  llvm_cbe_tmp__66 = (unsigned short )((unsigned short )llvm_cbe_tmp__65&65535U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = getelementptr inbounds i16* %%dst, i64 %%1, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_157_count);
  llvm_cbe_tmp__67 = (signed short *)(&llvm_cbe_dst[(((signed long long )llvm_cbe_tmp__1))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%66, i16* %%67, align 2, !dbg !6 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_158_count);
  *llvm_cbe_tmp__67 = llvm_cbe_tmp__66;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__66);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = add i32 %%storemerge1, 1, !dbg !7 for 0x%I64xth hint within @dct_1d  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__68 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__68&4294967295ull)));
  if (((llvm_cbe_tmp__68&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__69;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__68;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__69:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @dct_1d}\n");
  return;
}


void dct_2d(signed short (*llvm_cbe_in_block)[8], signed short (*llvm_cbe_out_block)[8]) {
  static  unsigned long long aesl_llvm_cbe_row_outbuf_count = 0;
  signed short llvm_cbe_row_outbuf[8][8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_col_outbuf_count = 0;
  signed short llvm_cbe_col_outbuf[8][8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_col_inbuf_count = 0;
  signed short llvm_cbe_col_inbuf[8][8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  signed short *llvm_cbe_tmp__70;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  signed short *llvm_cbe_tmp__71;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;
  static  unsigned long long aesl_llvm_cbe_198_count = 0;
  static  unsigned long long aesl_llvm_cbe_199_count = 0;
  static  unsigned long long aesl_llvm_cbe_200_count = 0;
  static  unsigned long long aesl_llvm_cbe_201_count = 0;
  static  unsigned long long aesl_llvm_cbe_202_count = 0;
  static  unsigned long long aesl_llvm_cbe_203_count = 0;
  static  unsigned long long aesl_llvm_cbe_204_count = 0;
  static  unsigned long long aesl_llvm_cbe_205_count = 0;
  static  unsigned long long aesl_llvm_cbe_206_count = 0;
  static  unsigned long long aesl_llvm_cbe_207_count = 0;
  static  unsigned long long aesl_llvm_cbe_208_count = 0;
  static  unsigned long long aesl_llvm_cbe_209_count = 0;
  static  unsigned long long aesl_llvm_cbe_210_count = 0;
  static  unsigned long long aesl_llvm_cbe_211_count = 0;
  signed short *llvm_cbe_tmp__72;
  static  unsigned long long aesl_llvm_cbe_212_count = 0;
  signed short *llvm_cbe_tmp__73;
  static  unsigned long long aesl_llvm_cbe_213_count = 0;
  static  unsigned long long aesl_llvm_cbe_214_count = 0;
  static  unsigned long long aesl_llvm_cbe_215_count = 0;
  static  unsigned long long aesl_llvm_cbe_216_count = 0;
  static  unsigned long long aesl_llvm_cbe_217_count = 0;
  static  unsigned long long aesl_llvm_cbe_218_count = 0;
  static  unsigned long long aesl_llvm_cbe_219_count = 0;
  static  unsigned long long aesl_llvm_cbe_220_count = 0;
  static  unsigned long long aesl_llvm_cbe_221_count = 0;
  static  unsigned long long aesl_llvm_cbe_222_count = 0;
  static  unsigned long long aesl_llvm_cbe_223_count = 0;
  static  unsigned long long aesl_llvm_cbe_224_count = 0;
  static  unsigned long long aesl_llvm_cbe_225_count = 0;
  static  unsigned long long aesl_llvm_cbe_226_count = 0;
  static  unsigned long long aesl_llvm_cbe_227_count = 0;
  static  unsigned long long aesl_llvm_cbe_228_count = 0;
  static  unsigned long long aesl_llvm_cbe_229_count = 0;
  static  unsigned long long aesl_llvm_cbe_230_count = 0;
  static  unsigned long long aesl_llvm_cbe_231_count = 0;
  signed short *llvm_cbe_tmp__74;
  static  unsigned long long aesl_llvm_cbe_232_count = 0;
  signed short *llvm_cbe_tmp__75;
  static  unsigned long long aesl_llvm_cbe_233_count = 0;
  static  unsigned long long aesl_llvm_cbe_234_count = 0;
  static  unsigned long long aesl_llvm_cbe_235_count = 0;
  static  unsigned long long aesl_llvm_cbe_236_count = 0;
  static  unsigned long long aesl_llvm_cbe_237_count = 0;
  static  unsigned long long aesl_llvm_cbe_238_count = 0;
  static  unsigned long long aesl_llvm_cbe_239_count = 0;
  static  unsigned long long aesl_llvm_cbe_240_count = 0;
  static  unsigned long long aesl_llvm_cbe_241_count = 0;
  static  unsigned long long aesl_llvm_cbe_242_count = 0;
  static  unsigned long long aesl_llvm_cbe_243_count = 0;
  static  unsigned long long aesl_llvm_cbe_244_count = 0;
  static  unsigned long long aesl_llvm_cbe_245_count = 0;
  static  unsigned long long aesl_llvm_cbe_246_count = 0;
  static  unsigned long long aesl_llvm_cbe_247_count = 0;
  static  unsigned long long aesl_llvm_cbe_248_count = 0;
  static  unsigned long long aesl_llvm_cbe_249_count = 0;
  static  unsigned long long aesl_llvm_cbe_250_count = 0;
  static  unsigned long long aesl_llvm_cbe_251_count = 0;
  signed short *llvm_cbe_tmp__76;
  static  unsigned long long aesl_llvm_cbe_252_count = 0;
  signed short *llvm_cbe_tmp__77;
  static  unsigned long long aesl_llvm_cbe_253_count = 0;
  static  unsigned long long aesl_llvm_cbe_254_count = 0;
  static  unsigned long long aesl_llvm_cbe_255_count = 0;
  static  unsigned long long aesl_llvm_cbe_256_count = 0;
  static  unsigned long long aesl_llvm_cbe_257_count = 0;
  static  unsigned long long aesl_llvm_cbe_258_count = 0;
  static  unsigned long long aesl_llvm_cbe_259_count = 0;
  static  unsigned long long aesl_llvm_cbe_260_count = 0;
  static  unsigned long long aesl_llvm_cbe_261_count = 0;
  static  unsigned long long aesl_llvm_cbe_262_count = 0;
  static  unsigned long long aesl_llvm_cbe_263_count = 0;
  static  unsigned long long aesl_llvm_cbe_264_count = 0;
  static  unsigned long long aesl_llvm_cbe_265_count = 0;
  static  unsigned long long aesl_llvm_cbe_266_count = 0;
  static  unsigned long long aesl_llvm_cbe_267_count = 0;
  static  unsigned long long aesl_llvm_cbe_268_count = 0;
  static  unsigned long long aesl_llvm_cbe_269_count = 0;
  static  unsigned long long aesl_llvm_cbe_270_count = 0;
  static  unsigned long long aesl_llvm_cbe_271_count = 0;
  signed short *llvm_cbe_tmp__78;
  static  unsigned long long aesl_llvm_cbe_272_count = 0;
  signed short *llvm_cbe_tmp__79;
  static  unsigned long long aesl_llvm_cbe_273_count = 0;
  static  unsigned long long aesl_llvm_cbe_274_count = 0;
  static  unsigned long long aesl_llvm_cbe_275_count = 0;
  static  unsigned long long aesl_llvm_cbe_276_count = 0;
  static  unsigned long long aesl_llvm_cbe_277_count = 0;
  static  unsigned long long aesl_llvm_cbe_278_count = 0;
  static  unsigned long long aesl_llvm_cbe_279_count = 0;
  static  unsigned long long aesl_llvm_cbe_280_count = 0;
  static  unsigned long long aesl_llvm_cbe_281_count = 0;
  static  unsigned long long aesl_llvm_cbe_282_count = 0;
  static  unsigned long long aesl_llvm_cbe_283_count = 0;
  static  unsigned long long aesl_llvm_cbe_284_count = 0;
  static  unsigned long long aesl_llvm_cbe_285_count = 0;
  static  unsigned long long aesl_llvm_cbe_286_count = 0;
  static  unsigned long long aesl_llvm_cbe_287_count = 0;
  static  unsigned long long aesl_llvm_cbe_288_count = 0;
  static  unsigned long long aesl_llvm_cbe_289_count = 0;
  static  unsigned long long aesl_llvm_cbe_290_count = 0;
  static  unsigned long long aesl_llvm_cbe_291_count = 0;
  signed short *llvm_cbe_tmp__80;
  static  unsigned long long aesl_llvm_cbe_292_count = 0;
  signed short *llvm_cbe_tmp__81;
  static  unsigned long long aesl_llvm_cbe_293_count = 0;
  static  unsigned long long aesl_llvm_cbe_294_count = 0;
  static  unsigned long long aesl_llvm_cbe_295_count = 0;
  static  unsigned long long aesl_llvm_cbe_296_count = 0;
  static  unsigned long long aesl_llvm_cbe_297_count = 0;
  static  unsigned long long aesl_llvm_cbe_298_count = 0;
  static  unsigned long long aesl_llvm_cbe_299_count = 0;
  static  unsigned long long aesl_llvm_cbe_300_count = 0;
  static  unsigned long long aesl_llvm_cbe_301_count = 0;
  static  unsigned long long aesl_llvm_cbe_302_count = 0;
  static  unsigned long long aesl_llvm_cbe_303_count = 0;
  static  unsigned long long aesl_llvm_cbe_304_count = 0;
  static  unsigned long long aesl_llvm_cbe_305_count = 0;
  static  unsigned long long aesl_llvm_cbe_306_count = 0;
  static  unsigned long long aesl_llvm_cbe_307_count = 0;
  static  unsigned long long aesl_llvm_cbe_308_count = 0;
  static  unsigned long long aesl_llvm_cbe_309_count = 0;
  static  unsigned long long aesl_llvm_cbe_310_count = 0;
  static  unsigned long long aesl_llvm_cbe_311_count = 0;
  signed short *llvm_cbe_tmp__82;
  static  unsigned long long aesl_llvm_cbe_312_count = 0;
  signed short *llvm_cbe_tmp__83;
  static  unsigned long long aesl_llvm_cbe_313_count = 0;
  static  unsigned long long aesl_llvm_cbe_314_count = 0;
  static  unsigned long long aesl_llvm_cbe_315_count = 0;
  static  unsigned long long aesl_llvm_cbe_316_count = 0;
  static  unsigned long long aesl_llvm_cbe_317_count = 0;
  static  unsigned long long aesl_llvm_cbe_318_count = 0;
  static  unsigned long long aesl_llvm_cbe_319_count = 0;
  static  unsigned long long aesl_llvm_cbe_320_count = 0;
  static  unsigned long long aesl_llvm_cbe_321_count = 0;
  static  unsigned long long aesl_llvm_cbe_322_count = 0;
  static  unsigned long long aesl_llvm_cbe_323_count = 0;
  static  unsigned long long aesl_llvm_cbe_324_count = 0;
  static  unsigned long long aesl_llvm_cbe_325_count = 0;
  static  unsigned long long aesl_llvm_cbe_326_count = 0;
  static  unsigned long long aesl_llvm_cbe_327_count = 0;
  static  unsigned long long aesl_llvm_cbe_328_count = 0;
  static  unsigned long long aesl_llvm_cbe_329_count = 0;
  static  unsigned long long aesl_llvm_cbe_330_count = 0;
  static  unsigned long long aesl_llvm_cbe_331_count = 0;
  signed short *llvm_cbe_tmp__84;
  static  unsigned long long aesl_llvm_cbe_332_count = 0;
  signed short *llvm_cbe_tmp__85;
  static  unsigned long long aesl_llvm_cbe_333_count = 0;
  static  unsigned long long aesl_llvm_cbe_334_count = 0;
  static  unsigned long long aesl_llvm_cbe_335_count = 0;
  static  unsigned long long aesl_llvm_cbe_336_count = 0;
  static  unsigned long long aesl_llvm_cbe_337_count = 0;
  static  unsigned long long aesl_llvm_cbe_338_count = 0;
  static  unsigned long long aesl_llvm_cbe_339_count = 0;
  static  unsigned long long aesl_llvm_cbe_340_count = 0;
  static  unsigned long long aesl_llvm_cbe_341_count = 0;
  static  unsigned long long aesl_llvm_cbe_342_count = 0;
  static  unsigned long long aesl_llvm_cbe_343_count = 0;
  static  unsigned long long aesl_llvm_cbe_344_count = 0;
  static  unsigned long long aesl_llvm_cbe_345_count = 0;
  static  unsigned long long aesl_llvm_cbe_346_count = 0;
  static  unsigned long long aesl_llvm_cbe_347_count = 0;
  static  unsigned long long aesl_llvm_cbe_348_count = 0;
  static  unsigned long long aesl_llvm_cbe_349_count = 0;
  static  unsigned long long aesl_llvm_cbe_350_count = 0;
  static  unsigned long long aesl_llvm_cbe_351_count = 0;
  static  unsigned long long aesl_llvm_cbe_352_count = 0;
  static  unsigned long long aesl_llvm_cbe_353_count = 0;
  static  unsigned long long aesl_llvm_cbe_354_count = 0;
  static  unsigned long long aesl_llvm_cbe_355_count = 0;
  static  unsigned long long aesl_llvm_cbe_356_count = 0;
  static  unsigned long long aesl_llvm_cbe_357_count = 0;
  static  unsigned long long aesl_llvm_cbe_358_count = 0;
  static  unsigned long long aesl_llvm_cbe_359_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge114_count = 0;
  unsigned int llvm_cbe_storemerge114;
  unsigned int llvm_cbe_storemerge114__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_360_count = 0;
  static  unsigned long long aesl_llvm_cbe_361_count = 0;
  static  unsigned long long aesl_llvm_cbe_362_count = 0;
  static  unsigned long long aesl_llvm_cbe_363_count = 0;
  static  unsigned long long aesl_llvm_cbe_364_count = 0;
  static  unsigned long long aesl_llvm_cbe_365_count = 0;
  static  unsigned long long aesl_llvm_cbe_366_count = 0;
  static  unsigned long long aesl_llvm_cbe_367_count = 0;
  static  unsigned long long aesl_llvm_cbe_368_count = 0;
  static  unsigned long long aesl_llvm_cbe_369_count = 0;
  static  unsigned long long aesl_llvm_cbe_370_count = 0;
  static  unsigned long long aesl_llvm_cbe_371_count = 0;
  static  unsigned long long aesl_llvm_cbe_372_count = 0;
  static  unsigned long long aesl_llvm_cbe_373_count = 0;
  static  unsigned long long aesl_llvm_cbe_374_count = 0;
  static  unsigned long long aesl_llvm_cbe_375_count = 0;
  static  unsigned long long aesl_llvm_cbe_376_count = 0;
  unsigned long long llvm_cbe_tmp__86;
  static  unsigned long long aesl_llvm_cbe_377_count = 0;
  signed short *llvm_cbe_tmp__87;
  static  unsigned long long aesl_llvm_cbe_378_count = 0;
  unsigned short llvm_cbe_tmp__88;
  static  unsigned long long aesl_llvm_cbe_379_count = 0;
  signed short *llvm_cbe_tmp__89;
  static  unsigned long long aesl_llvm_cbe_380_count = 0;
  static  unsigned long long aesl_llvm_cbe_381_count = 0;
  static  unsigned long long aesl_llvm_cbe_382_count = 0;
  static  unsigned long long aesl_llvm_cbe_383_count = 0;
  static  unsigned long long aesl_llvm_cbe_384_count = 0;
  static  unsigned long long aesl_llvm_cbe_385_count = 0;
  static  unsigned long long aesl_llvm_cbe_386_count = 0;
  static  unsigned long long aesl_llvm_cbe_387_count = 0;
  static  unsigned long long aesl_llvm_cbe_388_count = 0;
  static  unsigned long long aesl_llvm_cbe_389_count = 0;
  static  unsigned long long aesl_llvm_cbe_390_count = 0;
  static  unsigned long long aesl_llvm_cbe_391_count = 0;
  static  unsigned long long aesl_llvm_cbe_392_count = 0;
  static  unsigned long long aesl_llvm_cbe_393_count = 0;
  static  unsigned long long aesl_llvm_cbe_394_count = 0;
  static  unsigned long long aesl_llvm_cbe_395_count = 0;
  static  unsigned long long aesl_llvm_cbe_396_count = 0;
  static  unsigned long long aesl_llvm_cbe_397_count = 0;
  static  unsigned long long aesl_llvm_cbe_398_count = 0;
  signed short *llvm_cbe_tmp__90;
  static  unsigned long long aesl_llvm_cbe_399_count = 0;
  unsigned short llvm_cbe_tmp__91;
  static  unsigned long long aesl_llvm_cbe_400_count = 0;
  signed short *llvm_cbe_tmp__92;
  static  unsigned long long aesl_llvm_cbe_401_count = 0;
  static  unsigned long long aesl_llvm_cbe_402_count = 0;
  static  unsigned long long aesl_llvm_cbe_403_count = 0;
  static  unsigned long long aesl_llvm_cbe_404_count = 0;
  static  unsigned long long aesl_llvm_cbe_405_count = 0;
  static  unsigned long long aesl_llvm_cbe_406_count = 0;
  static  unsigned long long aesl_llvm_cbe_407_count = 0;
  static  unsigned long long aesl_llvm_cbe_408_count = 0;
  static  unsigned long long aesl_llvm_cbe_409_count = 0;
  static  unsigned long long aesl_llvm_cbe_410_count = 0;
  static  unsigned long long aesl_llvm_cbe_411_count = 0;
  static  unsigned long long aesl_llvm_cbe_412_count = 0;
  static  unsigned long long aesl_llvm_cbe_413_count = 0;
  static  unsigned long long aesl_llvm_cbe_414_count = 0;
  static  unsigned long long aesl_llvm_cbe_415_count = 0;
  static  unsigned long long aesl_llvm_cbe_416_count = 0;
  static  unsigned long long aesl_llvm_cbe_417_count = 0;
  static  unsigned long long aesl_llvm_cbe_418_count = 0;
  static  unsigned long long aesl_llvm_cbe_419_count = 0;
  signed short *llvm_cbe_tmp__93;
  static  unsigned long long aesl_llvm_cbe_420_count = 0;
  unsigned short llvm_cbe_tmp__94;
  static  unsigned long long aesl_llvm_cbe_421_count = 0;
  signed short *llvm_cbe_tmp__95;
  static  unsigned long long aesl_llvm_cbe_422_count = 0;
  static  unsigned long long aesl_llvm_cbe_423_count = 0;
  static  unsigned long long aesl_llvm_cbe_424_count = 0;
  static  unsigned long long aesl_llvm_cbe_425_count = 0;
  static  unsigned long long aesl_llvm_cbe_426_count = 0;
  static  unsigned long long aesl_llvm_cbe_427_count = 0;
  static  unsigned long long aesl_llvm_cbe_428_count = 0;
  static  unsigned long long aesl_llvm_cbe_429_count = 0;
  static  unsigned long long aesl_llvm_cbe_430_count = 0;
  static  unsigned long long aesl_llvm_cbe_431_count = 0;
  static  unsigned long long aesl_llvm_cbe_432_count = 0;
  static  unsigned long long aesl_llvm_cbe_433_count = 0;
  static  unsigned long long aesl_llvm_cbe_434_count = 0;
  static  unsigned long long aesl_llvm_cbe_435_count = 0;
  static  unsigned long long aesl_llvm_cbe_436_count = 0;
  static  unsigned long long aesl_llvm_cbe_437_count = 0;
  static  unsigned long long aesl_llvm_cbe_438_count = 0;
  static  unsigned long long aesl_llvm_cbe_439_count = 0;
  static  unsigned long long aesl_llvm_cbe_440_count = 0;
  signed short *llvm_cbe_tmp__96;
  static  unsigned long long aesl_llvm_cbe_441_count = 0;
  unsigned short llvm_cbe_tmp__97;
  static  unsigned long long aesl_llvm_cbe_442_count = 0;
  signed short *llvm_cbe_tmp__98;
  static  unsigned long long aesl_llvm_cbe_443_count = 0;
  static  unsigned long long aesl_llvm_cbe_444_count = 0;
  static  unsigned long long aesl_llvm_cbe_445_count = 0;
  static  unsigned long long aesl_llvm_cbe_446_count = 0;
  static  unsigned long long aesl_llvm_cbe_447_count = 0;
  static  unsigned long long aesl_llvm_cbe_448_count = 0;
  static  unsigned long long aesl_llvm_cbe_449_count = 0;
  static  unsigned long long aesl_llvm_cbe_450_count = 0;
  static  unsigned long long aesl_llvm_cbe_451_count = 0;
  static  unsigned long long aesl_llvm_cbe_452_count = 0;
  static  unsigned long long aesl_llvm_cbe_453_count = 0;
  static  unsigned long long aesl_llvm_cbe_454_count = 0;
  static  unsigned long long aesl_llvm_cbe_455_count = 0;
  static  unsigned long long aesl_llvm_cbe_456_count = 0;
  static  unsigned long long aesl_llvm_cbe_457_count = 0;
  static  unsigned long long aesl_llvm_cbe_458_count = 0;
  static  unsigned long long aesl_llvm_cbe_459_count = 0;
  static  unsigned long long aesl_llvm_cbe_460_count = 0;
  static  unsigned long long aesl_llvm_cbe_461_count = 0;
  signed short *llvm_cbe_tmp__99;
  static  unsigned long long aesl_llvm_cbe_462_count = 0;
  unsigned short llvm_cbe_tmp__100;
  static  unsigned long long aesl_llvm_cbe_463_count = 0;
  signed short *llvm_cbe_tmp__101;
  static  unsigned long long aesl_llvm_cbe_464_count = 0;
  static  unsigned long long aesl_llvm_cbe_465_count = 0;
  static  unsigned long long aesl_llvm_cbe_466_count = 0;
  static  unsigned long long aesl_llvm_cbe_467_count = 0;
  static  unsigned long long aesl_llvm_cbe_468_count = 0;
  static  unsigned long long aesl_llvm_cbe_469_count = 0;
  static  unsigned long long aesl_llvm_cbe_470_count = 0;
  static  unsigned long long aesl_llvm_cbe_471_count = 0;
  static  unsigned long long aesl_llvm_cbe_472_count = 0;
  static  unsigned long long aesl_llvm_cbe_473_count = 0;
  static  unsigned long long aesl_llvm_cbe_474_count = 0;
  static  unsigned long long aesl_llvm_cbe_475_count = 0;
  static  unsigned long long aesl_llvm_cbe_476_count = 0;
  static  unsigned long long aesl_llvm_cbe_477_count = 0;
  static  unsigned long long aesl_llvm_cbe_478_count = 0;
  static  unsigned long long aesl_llvm_cbe_479_count = 0;
  static  unsigned long long aesl_llvm_cbe_480_count = 0;
  static  unsigned long long aesl_llvm_cbe_481_count = 0;
  static  unsigned long long aesl_llvm_cbe_482_count = 0;
  signed short *llvm_cbe_tmp__102;
  static  unsigned long long aesl_llvm_cbe_483_count = 0;
  unsigned short llvm_cbe_tmp__103;
  static  unsigned long long aesl_llvm_cbe_484_count = 0;
  signed short *llvm_cbe_tmp__104;
  static  unsigned long long aesl_llvm_cbe_485_count = 0;
  static  unsigned long long aesl_llvm_cbe_486_count = 0;
  static  unsigned long long aesl_llvm_cbe_487_count = 0;
  static  unsigned long long aesl_llvm_cbe_488_count = 0;
  static  unsigned long long aesl_llvm_cbe_489_count = 0;
  static  unsigned long long aesl_llvm_cbe_490_count = 0;
  static  unsigned long long aesl_llvm_cbe_491_count = 0;
  static  unsigned long long aesl_llvm_cbe_492_count = 0;
  static  unsigned long long aesl_llvm_cbe_493_count = 0;
  static  unsigned long long aesl_llvm_cbe_494_count = 0;
  static  unsigned long long aesl_llvm_cbe_495_count = 0;
  static  unsigned long long aesl_llvm_cbe_496_count = 0;
  static  unsigned long long aesl_llvm_cbe_497_count = 0;
  static  unsigned long long aesl_llvm_cbe_498_count = 0;
  static  unsigned long long aesl_llvm_cbe_499_count = 0;
  static  unsigned long long aesl_llvm_cbe_500_count = 0;
  static  unsigned long long aesl_llvm_cbe_501_count = 0;
  static  unsigned long long aesl_llvm_cbe_502_count = 0;
  static  unsigned long long aesl_llvm_cbe_503_count = 0;
  signed short *llvm_cbe_tmp__105;
  static  unsigned long long aesl_llvm_cbe_504_count = 0;
  unsigned short llvm_cbe_tmp__106;
  static  unsigned long long aesl_llvm_cbe_505_count = 0;
  signed short *llvm_cbe_tmp__107;
  static  unsigned long long aesl_llvm_cbe_506_count = 0;
  static  unsigned long long aesl_llvm_cbe_507_count = 0;
  static  unsigned long long aesl_llvm_cbe_508_count = 0;
  static  unsigned long long aesl_llvm_cbe_509_count = 0;
  static  unsigned long long aesl_llvm_cbe_510_count = 0;
  static  unsigned long long aesl_llvm_cbe_511_count = 0;
  static  unsigned long long aesl_llvm_cbe_512_count = 0;
  static  unsigned long long aesl_llvm_cbe_513_count = 0;
  static  unsigned long long aesl_llvm_cbe_514_count = 0;
  static  unsigned long long aesl_llvm_cbe_515_count = 0;
  static  unsigned long long aesl_llvm_cbe_516_count = 0;
  static  unsigned long long aesl_llvm_cbe_517_count = 0;
  static  unsigned long long aesl_llvm_cbe_518_count = 0;
  static  unsigned long long aesl_llvm_cbe_519_count = 0;
  static  unsigned long long aesl_llvm_cbe_520_count = 0;
  static  unsigned long long aesl_llvm_cbe_521_count = 0;
  static  unsigned long long aesl_llvm_cbe_522_count = 0;
  static  unsigned long long aesl_llvm_cbe_523_count = 0;
  static  unsigned long long aesl_llvm_cbe_524_count = 0;
  signed short *llvm_cbe_tmp__108;
  static  unsigned long long aesl_llvm_cbe_525_count = 0;
  unsigned short llvm_cbe_tmp__109;
  static  unsigned long long aesl_llvm_cbe_526_count = 0;
  signed short *llvm_cbe_tmp__110;
  static  unsigned long long aesl_llvm_cbe_527_count = 0;
  static  unsigned long long aesl_llvm_cbe_528_count = 0;
  static  unsigned long long aesl_llvm_cbe_529_count = 0;
  static  unsigned long long aesl_llvm_cbe_530_count = 0;
  static  unsigned long long aesl_llvm_cbe_531_count = 0;
  static  unsigned long long aesl_llvm_cbe_532_count = 0;
  static  unsigned long long aesl_llvm_cbe_533_count = 0;
  static  unsigned long long aesl_llvm_cbe_534_count = 0;
  static  unsigned long long aesl_llvm_cbe_535_count = 0;
  static  unsigned long long aesl_llvm_cbe_536_count = 0;
  static  unsigned long long aesl_llvm_cbe_537_count = 0;
  static  unsigned long long aesl_llvm_cbe_538_count = 0;
  static  unsigned long long aesl_llvm_cbe_539_count = 0;
  static  unsigned long long aesl_llvm_cbe_540_count = 0;
  static  unsigned long long aesl_llvm_cbe_541_count = 0;
  static  unsigned long long aesl_llvm_cbe_542_count = 0;
  static  unsigned long long aesl_llvm_cbe_543_count = 0;
  static  unsigned long long aesl_llvm_cbe_544_count = 0;
  static  unsigned long long aesl_llvm_cbe_545_count = 0;
  unsigned int llvm_cbe_tmp__111;
  static  unsigned long long aesl_llvm_cbe_546_count = 0;
  static  unsigned long long aesl_llvm_cbe_547_count = 0;
  static  unsigned long long aesl_llvm_cbe_548_count = 0;
  static  unsigned long long aesl_llvm_cbe_549_count = 0;
  static  unsigned long long aesl_llvm_cbe_550_count = 0;
  static  unsigned long long aesl_llvm_cbe_551_count = 0;
  static  unsigned long long aesl_llvm_cbe_552_count = 0;
  static  unsigned long long aesl_llvm_cbe_553_count = 0;
  static  unsigned long long aesl_llvm_cbe_554_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond18_count = 0;
  static  unsigned long long aesl_llvm_cbe_555_count = 0;
  static  unsigned long long aesl_llvm_cbe_556_count = 0;
  static  unsigned long long aesl_llvm_cbe_557_count = 0;
  static  unsigned long long aesl_llvm_cbe_558_count = 0;
  static  unsigned long long aesl_llvm_cbe_559_count = 0;
  static  unsigned long long aesl_llvm_cbe_560_count = 0;
  static  unsigned long long aesl_llvm_cbe_561_count = 0;
  static  unsigned long long aesl_llvm_cbe_562_count = 0;
  static  unsigned long long aesl_llvm_cbe_563_count = 0;
  static  unsigned long long aesl_llvm_cbe_564_count = 0;
  static  unsigned long long aesl_llvm_cbe_565_count = 0;
  static  unsigned long long aesl_llvm_cbe_566_count = 0;
  static  unsigned long long aesl_llvm_cbe_567_count = 0;
  static  unsigned long long aesl_llvm_cbe_568_count = 0;
  static  unsigned long long aesl_llvm_cbe_569_count = 0;
  static  unsigned long long aesl_llvm_cbe_570_count = 0;
  static  unsigned long long aesl_llvm_cbe_571_count = 0;
  static  unsigned long long aesl_llvm_cbe_572_count = 0;
  signed short *llvm_cbe_tmp__112;
  static  unsigned long long aesl_llvm_cbe_573_count = 0;
  signed short *llvm_cbe_tmp__113;
  static  unsigned long long aesl_llvm_cbe_574_count = 0;
  static  unsigned long long aesl_llvm_cbe_575_count = 0;
  static  unsigned long long aesl_llvm_cbe_576_count = 0;
  static  unsigned long long aesl_llvm_cbe_577_count = 0;
  static  unsigned long long aesl_llvm_cbe_578_count = 0;
  static  unsigned long long aesl_llvm_cbe_579_count = 0;
  static  unsigned long long aesl_llvm_cbe_580_count = 0;
  static  unsigned long long aesl_llvm_cbe_581_count = 0;
  static  unsigned long long aesl_llvm_cbe_582_count = 0;
  static  unsigned long long aesl_llvm_cbe_583_count = 0;
  static  unsigned long long aesl_llvm_cbe_584_count = 0;
  static  unsigned long long aesl_llvm_cbe_585_count = 0;
  static  unsigned long long aesl_llvm_cbe_586_count = 0;
  static  unsigned long long aesl_llvm_cbe_587_count = 0;
  static  unsigned long long aesl_llvm_cbe_588_count = 0;
  static  unsigned long long aesl_llvm_cbe_589_count = 0;
  static  unsigned long long aesl_llvm_cbe_590_count = 0;
  static  unsigned long long aesl_llvm_cbe_591_count = 0;
  static  unsigned long long aesl_llvm_cbe_592_count = 0;
  signed short *llvm_cbe_tmp__114;
  static  unsigned long long aesl_llvm_cbe_593_count = 0;
  signed short *llvm_cbe_tmp__115;
  static  unsigned long long aesl_llvm_cbe_594_count = 0;
  static  unsigned long long aesl_llvm_cbe_595_count = 0;
  static  unsigned long long aesl_llvm_cbe_596_count = 0;
  static  unsigned long long aesl_llvm_cbe_597_count = 0;
  static  unsigned long long aesl_llvm_cbe_598_count = 0;
  static  unsigned long long aesl_llvm_cbe_599_count = 0;
  static  unsigned long long aesl_llvm_cbe_600_count = 0;
  static  unsigned long long aesl_llvm_cbe_601_count = 0;
  static  unsigned long long aesl_llvm_cbe_602_count = 0;
  static  unsigned long long aesl_llvm_cbe_603_count = 0;
  static  unsigned long long aesl_llvm_cbe_604_count = 0;
  static  unsigned long long aesl_llvm_cbe_605_count = 0;
  static  unsigned long long aesl_llvm_cbe_606_count = 0;
  static  unsigned long long aesl_llvm_cbe_607_count = 0;
  static  unsigned long long aesl_llvm_cbe_608_count = 0;
  static  unsigned long long aesl_llvm_cbe_609_count = 0;
  static  unsigned long long aesl_llvm_cbe_610_count = 0;
  static  unsigned long long aesl_llvm_cbe_611_count = 0;
  static  unsigned long long aesl_llvm_cbe_612_count = 0;
  signed short *llvm_cbe_tmp__116;
  static  unsigned long long aesl_llvm_cbe_613_count = 0;
  signed short *llvm_cbe_tmp__117;
  static  unsigned long long aesl_llvm_cbe_614_count = 0;
  static  unsigned long long aesl_llvm_cbe_615_count = 0;
  static  unsigned long long aesl_llvm_cbe_616_count = 0;
  static  unsigned long long aesl_llvm_cbe_617_count = 0;
  static  unsigned long long aesl_llvm_cbe_618_count = 0;
  static  unsigned long long aesl_llvm_cbe_619_count = 0;
  static  unsigned long long aesl_llvm_cbe_620_count = 0;
  static  unsigned long long aesl_llvm_cbe_621_count = 0;
  static  unsigned long long aesl_llvm_cbe_622_count = 0;
  static  unsigned long long aesl_llvm_cbe_623_count = 0;
  static  unsigned long long aesl_llvm_cbe_624_count = 0;
  static  unsigned long long aesl_llvm_cbe_625_count = 0;
  static  unsigned long long aesl_llvm_cbe_626_count = 0;
  static  unsigned long long aesl_llvm_cbe_627_count = 0;
  static  unsigned long long aesl_llvm_cbe_628_count = 0;
  static  unsigned long long aesl_llvm_cbe_629_count = 0;
  static  unsigned long long aesl_llvm_cbe_630_count = 0;
  static  unsigned long long aesl_llvm_cbe_631_count = 0;
  static  unsigned long long aesl_llvm_cbe_632_count = 0;
  signed short *llvm_cbe_tmp__118;
  static  unsigned long long aesl_llvm_cbe_633_count = 0;
  signed short *llvm_cbe_tmp__119;
  static  unsigned long long aesl_llvm_cbe_634_count = 0;
  static  unsigned long long aesl_llvm_cbe_635_count = 0;
  static  unsigned long long aesl_llvm_cbe_636_count = 0;
  static  unsigned long long aesl_llvm_cbe_637_count = 0;
  static  unsigned long long aesl_llvm_cbe_638_count = 0;
  static  unsigned long long aesl_llvm_cbe_639_count = 0;
  static  unsigned long long aesl_llvm_cbe_640_count = 0;
  static  unsigned long long aesl_llvm_cbe_641_count = 0;
  static  unsigned long long aesl_llvm_cbe_642_count = 0;
  static  unsigned long long aesl_llvm_cbe_643_count = 0;
  static  unsigned long long aesl_llvm_cbe_644_count = 0;
  static  unsigned long long aesl_llvm_cbe_645_count = 0;
  static  unsigned long long aesl_llvm_cbe_646_count = 0;
  static  unsigned long long aesl_llvm_cbe_647_count = 0;
  static  unsigned long long aesl_llvm_cbe_648_count = 0;
  static  unsigned long long aesl_llvm_cbe_649_count = 0;
  static  unsigned long long aesl_llvm_cbe_650_count = 0;
  static  unsigned long long aesl_llvm_cbe_651_count = 0;
  static  unsigned long long aesl_llvm_cbe_652_count = 0;
  signed short *llvm_cbe_tmp__120;
  static  unsigned long long aesl_llvm_cbe_653_count = 0;
  signed short *llvm_cbe_tmp__121;
  static  unsigned long long aesl_llvm_cbe_654_count = 0;
  static  unsigned long long aesl_llvm_cbe_655_count = 0;
  static  unsigned long long aesl_llvm_cbe_656_count = 0;
  static  unsigned long long aesl_llvm_cbe_657_count = 0;
  static  unsigned long long aesl_llvm_cbe_658_count = 0;
  static  unsigned long long aesl_llvm_cbe_659_count = 0;
  static  unsigned long long aesl_llvm_cbe_660_count = 0;
  static  unsigned long long aesl_llvm_cbe_661_count = 0;
  static  unsigned long long aesl_llvm_cbe_662_count = 0;
  static  unsigned long long aesl_llvm_cbe_663_count = 0;
  static  unsigned long long aesl_llvm_cbe_664_count = 0;
  static  unsigned long long aesl_llvm_cbe_665_count = 0;
  static  unsigned long long aesl_llvm_cbe_666_count = 0;
  static  unsigned long long aesl_llvm_cbe_667_count = 0;
  static  unsigned long long aesl_llvm_cbe_668_count = 0;
  static  unsigned long long aesl_llvm_cbe_669_count = 0;
  static  unsigned long long aesl_llvm_cbe_670_count = 0;
  static  unsigned long long aesl_llvm_cbe_671_count = 0;
  static  unsigned long long aesl_llvm_cbe_672_count = 0;
  signed short *llvm_cbe_tmp__122;
  static  unsigned long long aesl_llvm_cbe_673_count = 0;
  signed short *llvm_cbe_tmp__123;
  static  unsigned long long aesl_llvm_cbe_674_count = 0;
  static  unsigned long long aesl_llvm_cbe_675_count = 0;
  static  unsigned long long aesl_llvm_cbe_676_count = 0;
  static  unsigned long long aesl_llvm_cbe_677_count = 0;
  static  unsigned long long aesl_llvm_cbe_678_count = 0;
  static  unsigned long long aesl_llvm_cbe_679_count = 0;
  static  unsigned long long aesl_llvm_cbe_680_count = 0;
  static  unsigned long long aesl_llvm_cbe_681_count = 0;
  static  unsigned long long aesl_llvm_cbe_682_count = 0;
  static  unsigned long long aesl_llvm_cbe_683_count = 0;
  static  unsigned long long aesl_llvm_cbe_684_count = 0;
  static  unsigned long long aesl_llvm_cbe_685_count = 0;
  static  unsigned long long aesl_llvm_cbe_686_count = 0;
  static  unsigned long long aesl_llvm_cbe_687_count = 0;
  static  unsigned long long aesl_llvm_cbe_688_count = 0;
  static  unsigned long long aesl_llvm_cbe_689_count = 0;
  static  unsigned long long aesl_llvm_cbe_690_count = 0;
  static  unsigned long long aesl_llvm_cbe_691_count = 0;
  static  unsigned long long aesl_llvm_cbe_692_count = 0;
  signed short *llvm_cbe_tmp__124;
  static  unsigned long long aesl_llvm_cbe_693_count = 0;
  signed short *llvm_cbe_tmp__125;
  static  unsigned long long aesl_llvm_cbe_694_count = 0;
  static  unsigned long long aesl_llvm_cbe_695_count = 0;
  static  unsigned long long aesl_llvm_cbe_696_count = 0;
  static  unsigned long long aesl_llvm_cbe_697_count = 0;
  static  unsigned long long aesl_llvm_cbe_698_count = 0;
  static  unsigned long long aesl_llvm_cbe_699_count = 0;
  static  unsigned long long aesl_llvm_cbe_700_count = 0;
  static  unsigned long long aesl_llvm_cbe_701_count = 0;
  static  unsigned long long aesl_llvm_cbe_702_count = 0;
  static  unsigned long long aesl_llvm_cbe_703_count = 0;
  static  unsigned long long aesl_llvm_cbe_704_count = 0;
  static  unsigned long long aesl_llvm_cbe_705_count = 0;
  static  unsigned long long aesl_llvm_cbe_706_count = 0;
  static  unsigned long long aesl_llvm_cbe_707_count = 0;
  static  unsigned long long aesl_llvm_cbe_708_count = 0;
  static  unsigned long long aesl_llvm_cbe_709_count = 0;
  static  unsigned long long aesl_llvm_cbe_710_count = 0;
  static  unsigned long long aesl_llvm_cbe_711_count = 0;
  static  unsigned long long aesl_llvm_cbe_712_count = 0;
  signed short *llvm_cbe_tmp__126;
  static  unsigned long long aesl_llvm_cbe_713_count = 0;
  signed short *llvm_cbe_tmp__127;
  static  unsigned long long aesl_llvm_cbe_714_count = 0;
  static  unsigned long long aesl_llvm_cbe_715_count = 0;
  static  unsigned long long aesl_llvm_cbe_716_count = 0;
  static  unsigned long long aesl_llvm_cbe_717_count = 0;
  static  unsigned long long aesl_llvm_cbe_718_count = 0;
  static  unsigned long long aesl_llvm_cbe_719_count = 0;
  static  unsigned long long aesl_llvm_cbe_720_count = 0;
  static  unsigned long long aesl_llvm_cbe_721_count = 0;
  static  unsigned long long aesl_llvm_cbe_722_count = 0;
  static  unsigned long long aesl_llvm_cbe_723_count = 0;
  static  unsigned long long aesl_llvm_cbe_724_count = 0;
  static  unsigned long long aesl_llvm_cbe_725_count = 0;
  static  unsigned long long aesl_llvm_cbe_726_count = 0;
  static  unsigned long long aesl_llvm_cbe_727_count = 0;
  static  unsigned long long aesl_llvm_cbe_728_count = 0;
  static  unsigned long long aesl_llvm_cbe_729_count = 0;
  static  unsigned long long aesl_llvm_cbe_730_count = 0;
  static  unsigned long long aesl_llvm_cbe_731_count = 0;
  static  unsigned long long aesl_llvm_cbe_732_count = 0;
  static  unsigned long long aesl_llvm_cbe_733_count = 0;
  static  unsigned long long aesl_llvm_cbe_734_count = 0;
  static  unsigned long long aesl_llvm_cbe_735_count = 0;
  static  unsigned long long aesl_llvm_cbe_736_count = 0;
  static  unsigned long long aesl_llvm_cbe_737_count = 0;
  static  unsigned long long aesl_llvm_cbe_738_count = 0;
  static  unsigned long long aesl_llvm_cbe_739_count = 0;
  static  unsigned long long aesl_llvm_cbe_740_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge38_count = 0;
  unsigned int llvm_cbe_storemerge38;
  unsigned int llvm_cbe_storemerge38__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_741_count = 0;
  static  unsigned long long aesl_llvm_cbe_742_count = 0;
  static  unsigned long long aesl_llvm_cbe_743_count = 0;
  static  unsigned long long aesl_llvm_cbe_744_count = 0;
  static  unsigned long long aesl_llvm_cbe_745_count = 0;
  static  unsigned long long aesl_llvm_cbe_746_count = 0;
  static  unsigned long long aesl_llvm_cbe_747_count = 0;
  static  unsigned long long aesl_llvm_cbe_748_count = 0;
  static  unsigned long long aesl_llvm_cbe_749_count = 0;
  static  unsigned long long aesl_llvm_cbe_750_count = 0;
  static  unsigned long long aesl_llvm_cbe_751_count = 0;
  static  unsigned long long aesl_llvm_cbe_752_count = 0;
  static  unsigned long long aesl_llvm_cbe_753_count = 0;
  static  unsigned long long aesl_llvm_cbe_754_count = 0;
  static  unsigned long long aesl_llvm_cbe_755_count = 0;
  static  unsigned long long aesl_llvm_cbe_756_count = 0;
  static  unsigned long long aesl_llvm_cbe_757_count = 0;
  unsigned long long llvm_cbe_tmp__128;
  static  unsigned long long aesl_llvm_cbe_758_count = 0;
  signed short *llvm_cbe_tmp__129;
  static  unsigned long long aesl_llvm_cbe_759_count = 0;
  unsigned short llvm_cbe_tmp__130;
  static  unsigned long long aesl_llvm_cbe_760_count = 0;
  signed short *llvm_cbe_tmp__131;
  static  unsigned long long aesl_llvm_cbe_761_count = 0;
  static  unsigned long long aesl_llvm_cbe_762_count = 0;
  static  unsigned long long aesl_llvm_cbe_763_count = 0;
  static  unsigned long long aesl_llvm_cbe_764_count = 0;
  static  unsigned long long aesl_llvm_cbe_765_count = 0;
  static  unsigned long long aesl_llvm_cbe_766_count = 0;
  static  unsigned long long aesl_llvm_cbe_767_count = 0;
  static  unsigned long long aesl_llvm_cbe_768_count = 0;
  static  unsigned long long aesl_llvm_cbe_769_count = 0;
  static  unsigned long long aesl_llvm_cbe_770_count = 0;
  static  unsigned long long aesl_llvm_cbe_771_count = 0;
  static  unsigned long long aesl_llvm_cbe_772_count = 0;
  static  unsigned long long aesl_llvm_cbe_773_count = 0;
  static  unsigned long long aesl_llvm_cbe_774_count = 0;
  static  unsigned long long aesl_llvm_cbe_775_count = 0;
  static  unsigned long long aesl_llvm_cbe_776_count = 0;
  static  unsigned long long aesl_llvm_cbe_777_count = 0;
  static  unsigned long long aesl_llvm_cbe_778_count = 0;
  static  unsigned long long aesl_llvm_cbe_779_count = 0;
  signed short *llvm_cbe_tmp__132;
  static  unsigned long long aesl_llvm_cbe_780_count = 0;
  unsigned short llvm_cbe_tmp__133;
  static  unsigned long long aesl_llvm_cbe_781_count = 0;
  signed short *llvm_cbe_tmp__134;
  static  unsigned long long aesl_llvm_cbe_782_count = 0;
  static  unsigned long long aesl_llvm_cbe_783_count = 0;
  static  unsigned long long aesl_llvm_cbe_784_count = 0;
  static  unsigned long long aesl_llvm_cbe_785_count = 0;
  static  unsigned long long aesl_llvm_cbe_786_count = 0;
  static  unsigned long long aesl_llvm_cbe_787_count = 0;
  static  unsigned long long aesl_llvm_cbe_788_count = 0;
  static  unsigned long long aesl_llvm_cbe_789_count = 0;
  static  unsigned long long aesl_llvm_cbe_790_count = 0;
  static  unsigned long long aesl_llvm_cbe_791_count = 0;
  static  unsigned long long aesl_llvm_cbe_792_count = 0;
  static  unsigned long long aesl_llvm_cbe_793_count = 0;
  static  unsigned long long aesl_llvm_cbe_794_count = 0;
  static  unsigned long long aesl_llvm_cbe_795_count = 0;
  static  unsigned long long aesl_llvm_cbe_796_count = 0;
  static  unsigned long long aesl_llvm_cbe_797_count = 0;
  static  unsigned long long aesl_llvm_cbe_798_count = 0;
  static  unsigned long long aesl_llvm_cbe_799_count = 0;
  static  unsigned long long aesl_llvm_cbe_800_count = 0;
  signed short *llvm_cbe_tmp__135;
  static  unsigned long long aesl_llvm_cbe_801_count = 0;
  unsigned short llvm_cbe_tmp__136;
  static  unsigned long long aesl_llvm_cbe_802_count = 0;
  signed short *llvm_cbe_tmp__137;
  static  unsigned long long aesl_llvm_cbe_803_count = 0;
  static  unsigned long long aesl_llvm_cbe_804_count = 0;
  static  unsigned long long aesl_llvm_cbe_805_count = 0;
  static  unsigned long long aesl_llvm_cbe_806_count = 0;
  static  unsigned long long aesl_llvm_cbe_807_count = 0;
  static  unsigned long long aesl_llvm_cbe_808_count = 0;
  static  unsigned long long aesl_llvm_cbe_809_count = 0;
  static  unsigned long long aesl_llvm_cbe_810_count = 0;
  static  unsigned long long aesl_llvm_cbe_811_count = 0;
  static  unsigned long long aesl_llvm_cbe_812_count = 0;
  static  unsigned long long aesl_llvm_cbe_813_count = 0;
  static  unsigned long long aesl_llvm_cbe_814_count = 0;
  static  unsigned long long aesl_llvm_cbe_815_count = 0;
  static  unsigned long long aesl_llvm_cbe_816_count = 0;
  static  unsigned long long aesl_llvm_cbe_817_count = 0;
  static  unsigned long long aesl_llvm_cbe_818_count = 0;
  static  unsigned long long aesl_llvm_cbe_819_count = 0;
  static  unsigned long long aesl_llvm_cbe_820_count = 0;
  static  unsigned long long aesl_llvm_cbe_821_count = 0;
  signed short *llvm_cbe_tmp__138;
  static  unsigned long long aesl_llvm_cbe_822_count = 0;
  unsigned short llvm_cbe_tmp__139;
  static  unsigned long long aesl_llvm_cbe_823_count = 0;
  signed short *llvm_cbe_tmp__140;
  static  unsigned long long aesl_llvm_cbe_824_count = 0;
  static  unsigned long long aesl_llvm_cbe_825_count = 0;
  static  unsigned long long aesl_llvm_cbe_826_count = 0;
  static  unsigned long long aesl_llvm_cbe_827_count = 0;
  static  unsigned long long aesl_llvm_cbe_828_count = 0;
  static  unsigned long long aesl_llvm_cbe_829_count = 0;
  static  unsigned long long aesl_llvm_cbe_830_count = 0;
  static  unsigned long long aesl_llvm_cbe_831_count = 0;
  static  unsigned long long aesl_llvm_cbe_832_count = 0;
  static  unsigned long long aesl_llvm_cbe_833_count = 0;
  static  unsigned long long aesl_llvm_cbe_834_count = 0;
  static  unsigned long long aesl_llvm_cbe_835_count = 0;
  static  unsigned long long aesl_llvm_cbe_836_count = 0;
  static  unsigned long long aesl_llvm_cbe_837_count = 0;
  static  unsigned long long aesl_llvm_cbe_838_count = 0;
  static  unsigned long long aesl_llvm_cbe_839_count = 0;
  static  unsigned long long aesl_llvm_cbe_840_count = 0;
  static  unsigned long long aesl_llvm_cbe_841_count = 0;
  static  unsigned long long aesl_llvm_cbe_842_count = 0;
  signed short *llvm_cbe_tmp__141;
  static  unsigned long long aesl_llvm_cbe_843_count = 0;
  unsigned short llvm_cbe_tmp__142;
  static  unsigned long long aesl_llvm_cbe_844_count = 0;
  signed short *llvm_cbe_tmp__143;
  static  unsigned long long aesl_llvm_cbe_845_count = 0;
  static  unsigned long long aesl_llvm_cbe_846_count = 0;
  static  unsigned long long aesl_llvm_cbe_847_count = 0;
  static  unsigned long long aesl_llvm_cbe_848_count = 0;
  static  unsigned long long aesl_llvm_cbe_849_count = 0;
  static  unsigned long long aesl_llvm_cbe_850_count = 0;
  static  unsigned long long aesl_llvm_cbe_851_count = 0;
  static  unsigned long long aesl_llvm_cbe_852_count = 0;
  static  unsigned long long aesl_llvm_cbe_853_count = 0;
  static  unsigned long long aesl_llvm_cbe_854_count = 0;
  static  unsigned long long aesl_llvm_cbe_855_count = 0;
  static  unsigned long long aesl_llvm_cbe_856_count = 0;
  static  unsigned long long aesl_llvm_cbe_857_count = 0;
  static  unsigned long long aesl_llvm_cbe_858_count = 0;
  static  unsigned long long aesl_llvm_cbe_859_count = 0;
  static  unsigned long long aesl_llvm_cbe_860_count = 0;
  static  unsigned long long aesl_llvm_cbe_861_count = 0;
  static  unsigned long long aesl_llvm_cbe_862_count = 0;
  static  unsigned long long aesl_llvm_cbe_863_count = 0;
  signed short *llvm_cbe_tmp__144;
  static  unsigned long long aesl_llvm_cbe_864_count = 0;
  unsigned short llvm_cbe_tmp__145;
  static  unsigned long long aesl_llvm_cbe_865_count = 0;
  signed short *llvm_cbe_tmp__146;
  static  unsigned long long aesl_llvm_cbe_866_count = 0;
  static  unsigned long long aesl_llvm_cbe_867_count = 0;
  static  unsigned long long aesl_llvm_cbe_868_count = 0;
  static  unsigned long long aesl_llvm_cbe_869_count = 0;
  static  unsigned long long aesl_llvm_cbe_870_count = 0;
  static  unsigned long long aesl_llvm_cbe_871_count = 0;
  static  unsigned long long aesl_llvm_cbe_872_count = 0;
  static  unsigned long long aesl_llvm_cbe_873_count = 0;
  static  unsigned long long aesl_llvm_cbe_874_count = 0;
  static  unsigned long long aesl_llvm_cbe_875_count = 0;
  static  unsigned long long aesl_llvm_cbe_876_count = 0;
  static  unsigned long long aesl_llvm_cbe_877_count = 0;
  static  unsigned long long aesl_llvm_cbe_878_count = 0;
  static  unsigned long long aesl_llvm_cbe_879_count = 0;
  static  unsigned long long aesl_llvm_cbe_880_count = 0;
  static  unsigned long long aesl_llvm_cbe_881_count = 0;
  static  unsigned long long aesl_llvm_cbe_882_count = 0;
  static  unsigned long long aesl_llvm_cbe_883_count = 0;
  static  unsigned long long aesl_llvm_cbe_884_count = 0;
  signed short *llvm_cbe_tmp__147;
  static  unsigned long long aesl_llvm_cbe_885_count = 0;
  unsigned short llvm_cbe_tmp__148;
  static  unsigned long long aesl_llvm_cbe_886_count = 0;
  signed short *llvm_cbe_tmp__149;
  static  unsigned long long aesl_llvm_cbe_887_count = 0;
  static  unsigned long long aesl_llvm_cbe_888_count = 0;
  static  unsigned long long aesl_llvm_cbe_889_count = 0;
  static  unsigned long long aesl_llvm_cbe_890_count = 0;
  static  unsigned long long aesl_llvm_cbe_891_count = 0;
  static  unsigned long long aesl_llvm_cbe_892_count = 0;
  static  unsigned long long aesl_llvm_cbe_893_count = 0;
  static  unsigned long long aesl_llvm_cbe_894_count = 0;
  static  unsigned long long aesl_llvm_cbe_895_count = 0;
  static  unsigned long long aesl_llvm_cbe_896_count = 0;
  static  unsigned long long aesl_llvm_cbe_897_count = 0;
  static  unsigned long long aesl_llvm_cbe_898_count = 0;
  static  unsigned long long aesl_llvm_cbe_899_count = 0;
  static  unsigned long long aesl_llvm_cbe_900_count = 0;
  static  unsigned long long aesl_llvm_cbe_901_count = 0;
  static  unsigned long long aesl_llvm_cbe_902_count = 0;
  static  unsigned long long aesl_llvm_cbe_903_count = 0;
  static  unsigned long long aesl_llvm_cbe_904_count = 0;
  static  unsigned long long aesl_llvm_cbe_905_count = 0;
  signed short *llvm_cbe_tmp__150;
  static  unsigned long long aesl_llvm_cbe_906_count = 0;
  unsigned short llvm_cbe_tmp__151;
  static  unsigned long long aesl_llvm_cbe_907_count = 0;
  signed short *llvm_cbe_tmp__152;
  static  unsigned long long aesl_llvm_cbe_908_count = 0;
  static  unsigned long long aesl_llvm_cbe_909_count = 0;
  static  unsigned long long aesl_llvm_cbe_910_count = 0;
  static  unsigned long long aesl_llvm_cbe_911_count = 0;
  static  unsigned long long aesl_llvm_cbe_912_count = 0;
  static  unsigned long long aesl_llvm_cbe_913_count = 0;
  static  unsigned long long aesl_llvm_cbe_914_count = 0;
  static  unsigned long long aesl_llvm_cbe_915_count = 0;
  static  unsigned long long aesl_llvm_cbe_916_count = 0;
  static  unsigned long long aesl_llvm_cbe_917_count = 0;
  static  unsigned long long aesl_llvm_cbe_918_count = 0;
  static  unsigned long long aesl_llvm_cbe_919_count = 0;
  static  unsigned long long aesl_llvm_cbe_920_count = 0;
  static  unsigned long long aesl_llvm_cbe_921_count = 0;
  static  unsigned long long aesl_llvm_cbe_922_count = 0;
  static  unsigned long long aesl_llvm_cbe_923_count = 0;
  static  unsigned long long aesl_llvm_cbe_924_count = 0;
  static  unsigned long long aesl_llvm_cbe_925_count = 0;
  static  unsigned long long aesl_llvm_cbe_926_count = 0;
  unsigned int llvm_cbe_tmp__153;
  static  unsigned long long aesl_llvm_cbe_927_count = 0;
  static  unsigned long long aesl_llvm_cbe_928_count = 0;
  static  unsigned long long aesl_llvm_cbe_929_count = 0;
  static  unsigned long long aesl_llvm_cbe_930_count = 0;
  static  unsigned long long aesl_llvm_cbe_931_count = 0;
  static  unsigned long long aesl_llvm_cbe_932_count = 0;
  static  unsigned long long aesl_llvm_cbe_933_count = 0;
  static  unsigned long long aesl_llvm_cbe_934_count = 0;
  static  unsigned long long aesl_llvm_cbe_935_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_936_count = 0;
  static  unsigned long long aesl_llvm_cbe_937_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @dct_2d\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%0 = getelementptr inbounds [8 x i16]* %%in_block, i64 0, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_191_count);
  llvm_cbe_tmp__70 = (signed short *)(&(*llvm_cbe_in_block)[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 0, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_192_count);
  llvm_cbe_tmp__71 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%0, i16* %%1), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_193_count);
  dct_1d((signed short *)llvm_cbe_tmp__70, (signed short *)llvm_cbe_tmp__71);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds [8 x i16]* %%in_block, i64 1, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_211_count);
  llvm_cbe_tmp__72 = (signed short *)(&llvm_cbe_in_block[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 1, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_212_count);
  llvm_cbe_tmp__73 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%2, i16* %%3), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_213_count);
  dct_1d((signed short *)llvm_cbe_tmp__72, (signed short *)llvm_cbe_tmp__73);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds [8 x i16]* %%in_block, i64 2, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_231_count);
  llvm_cbe_tmp__74 = (signed short *)(&llvm_cbe_in_block[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 2, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_232_count);
  llvm_cbe_tmp__75 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%4, i16* %%5), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_233_count);
  dct_1d((signed short *)llvm_cbe_tmp__74, (signed short *)llvm_cbe_tmp__75);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds [8 x i16]* %%in_block, i64 3, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_251_count);
  llvm_cbe_tmp__76 = (signed short *)(&llvm_cbe_in_block[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 3, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_252_count);
  llvm_cbe_tmp__77 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%6, i16* %%7), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_253_count);
  dct_1d((signed short *)llvm_cbe_tmp__76, (signed short *)llvm_cbe_tmp__77);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds [8 x i16]* %%in_block, i64 4, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_271_count);
  llvm_cbe_tmp__78 = (signed short *)(&llvm_cbe_in_block[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 4, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_272_count);
  llvm_cbe_tmp__79 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%8, i16* %%9), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_273_count);
  dct_1d((signed short *)llvm_cbe_tmp__78, (signed short *)llvm_cbe_tmp__79);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds [8 x i16]* %%in_block, i64 5, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_291_count);
  llvm_cbe_tmp__80 = (signed short *)(&llvm_cbe_in_block[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 5, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_292_count);
  llvm_cbe_tmp__81 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%10, i16* %%11), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_293_count);
  dct_1d((signed short *)llvm_cbe_tmp__80, (signed short *)llvm_cbe_tmp__81);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds [8 x i16]* %%in_block, i64 6, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_311_count);
  llvm_cbe_tmp__82 = (signed short *)(&llvm_cbe_in_block[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 6, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_312_count);
  llvm_cbe_tmp__83 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%12, i16* %%13), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_313_count);
  dct_1d((signed short *)llvm_cbe_tmp__82, (signed short *)llvm_cbe_tmp__83);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds [8 x i16]* %%in_block, i64 7, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_331_count);
  llvm_cbe_tmp__84 = (signed short *)(&llvm_cbe_in_block[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 7, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_332_count);
  llvm_cbe_tmp__85 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%14, i16* %%15), !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_333_count);
  dct_1d((signed short *)llvm_cbe_tmp__84, (signed short *)llvm_cbe_tmp__85);
if (AESL_DEBUG_TRACE) {
}
  llvm_cbe_storemerge114__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader11;

  do {     /* Syntactic loop '.preheader11' to make GCC happy */
llvm_cbe__2e_preheader11:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge114 = phi i32 [ 0, %%.preheader13 ], [ %%41, %%.preheader11  for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_storemerge114_count);
  llvm_cbe_storemerge114 = (unsigned int )llvm_cbe_storemerge114__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge114 = 0x%X",llvm_cbe_storemerge114);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__111);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = zext i32 %%storemerge114 to i64, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_376_count);
  llvm_cbe_tmp__86 = (unsigned long long )((unsigned long long )(unsigned int )llvm_cbe_storemerge114&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__86);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 0, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_377_count);
  llvm_cbe_tmp__87 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )0ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = load i16* %%17, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_378_count);
  llvm_cbe_tmp__88 = (unsigned short )*llvm_cbe_tmp__87;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_379_count);
  llvm_cbe_tmp__89 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )0ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%18, i16* %%19, align 16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_380_count);
  *llvm_cbe_tmp__89 = llvm_cbe_tmp__88;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__88);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 1, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_398_count);
  llvm_cbe_tmp__90 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )1ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = load i16* %%20, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_399_count);
  llvm_cbe_tmp__91 = (unsigned short )*llvm_cbe_tmp__90;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__91);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 1, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_400_count);
  llvm_cbe_tmp__92 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )1ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%21, i16* %%22, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_401_count);
  *llvm_cbe_tmp__92 = llvm_cbe_tmp__91;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__91);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 2, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_419_count);
  llvm_cbe_tmp__93 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )2ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = load i16* %%23, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_420_count);
  llvm_cbe_tmp__94 = (unsigned short )*llvm_cbe_tmp__93;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__94);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_421_count);
  llvm_cbe_tmp__95 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )2ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%24, i16* %%25, align 4, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_422_count);
  *llvm_cbe_tmp__95 = llvm_cbe_tmp__94;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__94);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 3, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_440_count);
  llvm_cbe_tmp__96 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )3ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = load i16* %%26, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_441_count);
  llvm_cbe_tmp__97 = (unsigned short )*llvm_cbe_tmp__96;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__97);
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 3, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_442_count);
  llvm_cbe_tmp__98 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )3ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%27, i16* %%28, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_443_count);
  *llvm_cbe_tmp__98 = llvm_cbe_tmp__97;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__97);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 4, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_461_count);
  llvm_cbe_tmp__99 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )4ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = load i16* %%29, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_462_count);
  llvm_cbe_tmp__100 = (unsigned short )*llvm_cbe_tmp__99;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__100);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 4, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_463_count);
  llvm_cbe_tmp__101 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )4ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%30, i16* %%31, align 8, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_464_count);
  *llvm_cbe_tmp__101 = llvm_cbe_tmp__100;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__100);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 5, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_482_count);
  llvm_cbe_tmp__102 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )5ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i16* %%32, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_483_count);
  llvm_cbe_tmp__103 = (unsigned short )*llvm_cbe_tmp__102;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__103);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 5, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_484_count);
  llvm_cbe_tmp__104 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )5ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%33, i16* %%34, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_485_count);
  *llvm_cbe_tmp__104 = llvm_cbe_tmp__103;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__103);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 6, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_503_count);
  llvm_cbe_tmp__105 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )6ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = load i16* %%35, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_504_count);
  llvm_cbe_tmp__106 = (unsigned short )*llvm_cbe_tmp__105;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__106);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 6, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_505_count);
  llvm_cbe_tmp__107 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )6ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%36, i16* %%37, align 4, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_506_count);
  *llvm_cbe_tmp__107 = llvm_cbe_tmp__106;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__106);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = getelementptr inbounds [8 x [8 x i16]]* %%row_outbuf, i64 0, i64 7, i64 %%16, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_524_count);
  llvm_cbe_tmp__108 = (signed short *)(&llvm_cbe_row_outbuf[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )7ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__86) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'row_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = load i16* %%38, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_525_count);
  llvm_cbe_tmp__109 = (unsigned short )*llvm_cbe_tmp__108;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__109);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 %%16, i64 7, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_526_count);
  llvm_cbe_tmp__110 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )llvm_cbe_tmp__86))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__86));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )llvm_cbe_tmp__86) < 8 && "Write access out of array 'col_inbuf' bound?");
  assert(((signed long long )7ull) < 8 && "Write access out of array 'col_inbuf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%39, i16* %%40, align 2, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_527_count);
  *llvm_cbe_tmp__110 = llvm_cbe_tmp__109;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__109);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = add i32 %%storemerge114, 1, !dbg !9 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_545_count);
  llvm_cbe_tmp__111 = (unsigned int )((unsigned int )(llvm_cbe_storemerge114&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__111&4294967295ull)));
  if (((llvm_cbe_tmp__111&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe__2e_preheader9;
  } else {
    llvm_cbe_storemerge114__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__111;   /* for PHI node */
    goto llvm_cbe__2e_preheader11;
  }

  } while (1); /* end of syntactic loop '.preheader11' */
llvm_cbe__2e_preheader9:
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 0, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_572_count);
  llvm_cbe_tmp__112 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 0, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_573_count);
  llvm_cbe_tmp__113 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%42, i16* %%43), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_574_count);
  dct_1d((signed short *)llvm_cbe_tmp__112, (signed short *)llvm_cbe_tmp__113);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 1, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_592_count);
  llvm_cbe_tmp__114 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 1, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_593_count);
  llvm_cbe_tmp__115 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%44, i16* %%45), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_594_count);
  dct_1d((signed short *)llvm_cbe_tmp__114, (signed short *)llvm_cbe_tmp__115);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 2, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_612_count);
  llvm_cbe_tmp__116 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 2, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_613_count);
  llvm_cbe_tmp__117 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%46, i16* %%47), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_614_count);
  dct_1d((signed short *)llvm_cbe_tmp__116, (signed short *)llvm_cbe_tmp__117);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 3, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_632_count);
  llvm_cbe_tmp__118 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 3, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_633_count);
  llvm_cbe_tmp__119 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%48, i16* %%49), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_634_count);
  dct_1d((signed short *)llvm_cbe_tmp__118, (signed short *)llvm_cbe_tmp__119);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 4, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_652_count);
  llvm_cbe_tmp__120 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 4, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_653_count);
  llvm_cbe_tmp__121 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%50, i16* %%51), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_654_count);
  dct_1d((signed short *)llvm_cbe_tmp__120, (signed short *)llvm_cbe_tmp__121);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 5, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_672_count);
  llvm_cbe_tmp__122 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 5, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_673_count);
  llvm_cbe_tmp__123 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%52, i16* %%53), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_674_count);
  dct_1d((signed short *)llvm_cbe_tmp__122, (signed short *)llvm_cbe_tmp__123);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 6, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_692_count);
  llvm_cbe_tmp__124 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 6, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_693_count);
  llvm_cbe_tmp__125 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%54, i16* %%55), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_694_count);
  dct_1d((signed short *)llvm_cbe_tmp__124, (signed short *)llvm_cbe_tmp__125);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = getelementptr inbounds [8 x [8 x i16]]* %%col_inbuf, i64 0, i64 7, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_712_count);
  llvm_cbe_tmp__126 = (signed short *)(&llvm_cbe_col_inbuf[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 7, i64 0, !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_713_count);
  llvm_cbe_tmp__127 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_1d(i16* %%56, i16* %%57), !dbg !8 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_714_count);
  dct_1d((signed short *)llvm_cbe_tmp__126, (signed short *)llvm_cbe_tmp__127);
if (AESL_DEBUG_TRACE) {
}
  llvm_cbe_storemerge38__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge38 = phi i32 [ 0, %%.preheader9 ], [ %%83, %%.preheader  for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_storemerge38_count);
  llvm_cbe_storemerge38 = (unsigned int )llvm_cbe_storemerge38__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge38 = 0x%X",llvm_cbe_storemerge38);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__153);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = zext i32 %%storemerge38 to i64, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_757_count);
  llvm_cbe_tmp__128 = (unsigned long long )((unsigned long long )(unsigned int )llvm_cbe_storemerge38&4294967295U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__128);
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 0, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_758_count);
  llvm_cbe_tmp__129 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )0ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = load i16* %%59, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_759_count);
  llvm_cbe_tmp__130 = (unsigned short )*llvm_cbe_tmp__129;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__130);
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 0, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_760_count);
  llvm_cbe_tmp__131 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%60, i16* %%61, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_761_count);
  *llvm_cbe_tmp__131 = llvm_cbe_tmp__130;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__130);
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 1, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_779_count);
  llvm_cbe_tmp__132 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )1ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )1ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%63 = load i16* %%62, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_780_count);
  llvm_cbe_tmp__133 = (unsigned short )*llvm_cbe_tmp__132;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__133);
if (AESL_DEBUG_TRACE)
printf("\n  %%64 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 1, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_781_count);
  llvm_cbe_tmp__134 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )1ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%63, i16* %%64, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_782_count);
  *llvm_cbe_tmp__134 = llvm_cbe_tmp__133;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__133);
if (AESL_DEBUG_TRACE)
printf("\n  %%65 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 2, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_800_count);
  llvm_cbe_tmp__135 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )2ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )2ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%66 = load i16* %%65, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_801_count);
  llvm_cbe_tmp__136 = (unsigned short )*llvm_cbe_tmp__135;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__136);
if (AESL_DEBUG_TRACE)
printf("\n  %%67 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_802_count);
  llvm_cbe_tmp__137 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )2ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )2ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%66, i16* %%67, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_803_count);
  *llvm_cbe_tmp__137 = llvm_cbe_tmp__136;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__136);
if (AESL_DEBUG_TRACE)
printf("\n  %%68 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 3, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_821_count);
  llvm_cbe_tmp__138 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )3ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )3ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%69 = load i16* %%68, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_822_count);
  llvm_cbe_tmp__139 = (unsigned short )*llvm_cbe_tmp__138;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__139);
if (AESL_DEBUG_TRACE)
printf("\n  %%70 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 3, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_823_count);
  llvm_cbe_tmp__140 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )3ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )3ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%69, i16* %%70, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_824_count);
  *llvm_cbe_tmp__140 = llvm_cbe_tmp__139;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__139);
if (AESL_DEBUG_TRACE)
printf("\n  %%71 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 4, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_842_count);
  llvm_cbe_tmp__141 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )4ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )4ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%72 = load i16* %%71, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_843_count);
  llvm_cbe_tmp__142 = (unsigned short )*llvm_cbe_tmp__141;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__142);
if (AESL_DEBUG_TRACE)
printf("\n  %%73 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 4, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_844_count);
  llvm_cbe_tmp__143 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )4ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )4ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%72, i16* %%73, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_845_count);
  *llvm_cbe_tmp__143 = llvm_cbe_tmp__142;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__142);
if (AESL_DEBUG_TRACE)
printf("\n  %%74 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 5, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_863_count);
  llvm_cbe_tmp__144 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )5ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )5ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%75 = load i16* %%74, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_864_count);
  llvm_cbe_tmp__145 = (unsigned short )*llvm_cbe_tmp__144;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__145);
if (AESL_DEBUG_TRACE)
printf("\n  %%76 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 5, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_865_count);
  llvm_cbe_tmp__146 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )5ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )5ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%75, i16* %%76, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_866_count);
  *llvm_cbe_tmp__146 = llvm_cbe_tmp__145;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__145);
if (AESL_DEBUG_TRACE)
printf("\n  %%77 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 6, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_884_count);
  llvm_cbe_tmp__147 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )6ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )6ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%78 = load i16* %%77, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_885_count);
  llvm_cbe_tmp__148 = (unsigned short )*llvm_cbe_tmp__147;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__148);
if (AESL_DEBUG_TRACE)
printf("\n  %%79 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 6, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_886_count);
  llvm_cbe_tmp__149 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )6ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )6ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%78, i16* %%79, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_887_count);
  *llvm_cbe_tmp__149 = llvm_cbe_tmp__148;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__148);
if (AESL_DEBUG_TRACE)
printf("\n  %%80 = getelementptr inbounds [8 x [8 x i16]]* %%col_outbuf, i64 0, i64 7, i64 %%58, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_905_count);
  llvm_cbe_tmp__150 = (signed short *)(&llvm_cbe_col_outbuf[(((signed long long )7ull))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )7ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);
  if (!(((signed long long )llvm_cbe_tmp__128) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'col_outbuf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%81 = load i16* %%80, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_906_count);
  llvm_cbe_tmp__151 = (unsigned short )*llvm_cbe_tmp__150;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__151);
if (AESL_DEBUG_TRACE)
printf("\n  %%82 = getelementptr inbounds [8 x i16]* %%out_block, i64 %%58, i64 7, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_907_count);
  llvm_cbe_tmp__152 = (signed short *)(&llvm_cbe_out_block[(((signed long long )llvm_cbe_tmp__128))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__128));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )7ull) < 8 && "Write access out of array 'out_block' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%81, i16* %%82, align 2, !dbg !6 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_908_count);
  *llvm_cbe_tmp__152 = llvm_cbe_tmp__151;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__151);
if (AESL_DEBUG_TRACE)
printf("\n  %%83 = add i32 %%storemerge38, 1, !dbg !9 for 0x%I64xth hint within @dct_2d  --> \n", ++aesl_llvm_cbe_926_count);
  llvm_cbe_tmp__153 = (unsigned int )((unsigned int )(llvm_cbe_storemerge38&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__153&4294967295ull)));
  if (((llvm_cbe_tmp__153&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__154;
  } else {
    llvm_cbe_storemerge38__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__153;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__154:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @dct_2d}\n");
  return;
}


void read_data(signed short *llvm_cbe_input, signed short (*llvm_cbe_buf)[8]) {
  static  unsigned long long aesl_llvm_cbe_938_count = 0;
  static  unsigned long long aesl_llvm_cbe_939_count = 0;
  static  unsigned long long aesl_llvm_cbe_940_count = 0;
  static  unsigned long long aesl_llvm_cbe_941_count = 0;
  static  unsigned long long aesl_llvm_cbe_942_count = 0;
  static  unsigned long long aesl_llvm_cbe_943_count = 0;
  static  unsigned long long aesl_llvm_cbe_944_count = 0;
  static  unsigned long long aesl_llvm_cbe_945_count = 0;
  static  unsigned long long aesl_llvm_cbe_946_count = 0;
  static  unsigned long long aesl_llvm_cbe_947_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_948_count = 0;
  static  unsigned long long aesl_llvm_cbe_949_count = 0;
  static  unsigned long long aesl_llvm_cbe_950_count = 0;
  static  unsigned long long aesl_llvm_cbe_951_count = 0;
  static  unsigned long long aesl_llvm_cbe_952_count = 0;
  unsigned int llvm_cbe_tmp__155;
  static  unsigned long long aesl_llvm_cbe_953_count = 0;
  unsigned long long llvm_cbe_tmp__156;
  static  unsigned long long aesl_llvm_cbe_954_count = 0;
  unsigned long long llvm_cbe_tmp__157;
  static  unsigned long long aesl_llvm_cbe_955_count = 0;
  signed short *llvm_cbe_tmp__158;
  static  unsigned long long aesl_llvm_cbe_956_count = 0;
  unsigned short llvm_cbe_tmp__159;
  static  unsigned long long aesl_llvm_cbe_957_count = 0;
  signed short *llvm_cbe_tmp__160;
  static  unsigned long long aesl_llvm_cbe_958_count = 0;
  static  unsigned long long aesl_llvm_cbe_959_count = 0;
  static  unsigned long long aesl_llvm_cbe_960_count = 0;
  static  unsigned long long aesl_llvm_cbe_961_count = 0;
  static  unsigned long long aesl_llvm_cbe_962_count = 0;
  static  unsigned long long aesl_llvm_cbe_963_count = 0;
  static  unsigned long long aesl_llvm_cbe_964_count = 0;
  unsigned int llvm_cbe_tmp__161;
  static  unsigned long long aesl_llvm_cbe_965_count = 0;
  unsigned long long llvm_cbe_tmp__162;
  static  unsigned long long aesl_llvm_cbe_966_count = 0;
  signed short *llvm_cbe_tmp__163;
  static  unsigned long long aesl_llvm_cbe_967_count = 0;
  unsigned short llvm_cbe_tmp__164;
  static  unsigned long long aesl_llvm_cbe_968_count = 0;
  signed short *llvm_cbe_tmp__165;
  static  unsigned long long aesl_llvm_cbe_969_count = 0;
  static  unsigned long long aesl_llvm_cbe_970_count = 0;
  static  unsigned long long aesl_llvm_cbe_971_count = 0;
  static  unsigned long long aesl_llvm_cbe_972_count = 0;
  static  unsigned long long aesl_llvm_cbe_973_count = 0;
  static  unsigned long long aesl_llvm_cbe_974_count = 0;
  static  unsigned long long aesl_llvm_cbe_975_count = 0;
  unsigned int llvm_cbe_tmp__166;
  static  unsigned long long aesl_llvm_cbe_976_count = 0;
  unsigned long long llvm_cbe_tmp__167;
  static  unsigned long long aesl_llvm_cbe_977_count = 0;
  signed short *llvm_cbe_tmp__168;
  static  unsigned long long aesl_llvm_cbe_978_count = 0;
  unsigned short llvm_cbe_tmp__169;
  static  unsigned long long aesl_llvm_cbe_979_count = 0;
  signed short *llvm_cbe_tmp__170;
  static  unsigned long long aesl_llvm_cbe_980_count = 0;
  static  unsigned long long aesl_llvm_cbe_981_count = 0;
  static  unsigned long long aesl_llvm_cbe_982_count = 0;
  static  unsigned long long aesl_llvm_cbe_983_count = 0;
  static  unsigned long long aesl_llvm_cbe_984_count = 0;
  static  unsigned long long aesl_llvm_cbe_985_count = 0;
  static  unsigned long long aesl_llvm_cbe_986_count = 0;
  unsigned int llvm_cbe_tmp__171;
  static  unsigned long long aesl_llvm_cbe_987_count = 0;
  unsigned long long llvm_cbe_tmp__172;
  static  unsigned long long aesl_llvm_cbe_988_count = 0;
  signed short *llvm_cbe_tmp__173;
  static  unsigned long long aesl_llvm_cbe_989_count = 0;
  unsigned short llvm_cbe_tmp__174;
  static  unsigned long long aesl_llvm_cbe_990_count = 0;
  signed short *llvm_cbe_tmp__175;
  static  unsigned long long aesl_llvm_cbe_991_count = 0;
  static  unsigned long long aesl_llvm_cbe_992_count = 0;
  static  unsigned long long aesl_llvm_cbe_993_count = 0;
  static  unsigned long long aesl_llvm_cbe_994_count = 0;
  static  unsigned long long aesl_llvm_cbe_995_count = 0;
  static  unsigned long long aesl_llvm_cbe_996_count = 0;
  static  unsigned long long aesl_llvm_cbe_997_count = 0;
  unsigned int llvm_cbe_tmp__176;
  static  unsigned long long aesl_llvm_cbe_998_count = 0;
  unsigned long long llvm_cbe_tmp__177;
  static  unsigned long long aesl_llvm_cbe_999_count = 0;
  signed short *llvm_cbe_tmp__178;
  static  unsigned long long aesl_llvm_cbe_1000_count = 0;
  unsigned short llvm_cbe_tmp__179;
  static  unsigned long long aesl_llvm_cbe_1001_count = 0;
  signed short *llvm_cbe_tmp__180;
  static  unsigned long long aesl_llvm_cbe_1002_count = 0;
  static  unsigned long long aesl_llvm_cbe_1003_count = 0;
  static  unsigned long long aesl_llvm_cbe_1004_count = 0;
  static  unsigned long long aesl_llvm_cbe_1005_count = 0;
  static  unsigned long long aesl_llvm_cbe_1006_count = 0;
  static  unsigned long long aesl_llvm_cbe_1007_count = 0;
  static  unsigned long long aesl_llvm_cbe_1008_count = 0;
  unsigned int llvm_cbe_tmp__181;
  static  unsigned long long aesl_llvm_cbe_1009_count = 0;
  unsigned long long llvm_cbe_tmp__182;
  static  unsigned long long aesl_llvm_cbe_1010_count = 0;
  signed short *llvm_cbe_tmp__183;
  static  unsigned long long aesl_llvm_cbe_1011_count = 0;
  unsigned short llvm_cbe_tmp__184;
  static  unsigned long long aesl_llvm_cbe_1012_count = 0;
  signed short *llvm_cbe_tmp__185;
  static  unsigned long long aesl_llvm_cbe_1013_count = 0;
  static  unsigned long long aesl_llvm_cbe_1014_count = 0;
  static  unsigned long long aesl_llvm_cbe_1015_count = 0;
  static  unsigned long long aesl_llvm_cbe_1016_count = 0;
  static  unsigned long long aesl_llvm_cbe_1017_count = 0;
  static  unsigned long long aesl_llvm_cbe_1018_count = 0;
  static  unsigned long long aesl_llvm_cbe_1019_count = 0;
  unsigned int llvm_cbe_tmp__186;
  static  unsigned long long aesl_llvm_cbe_1020_count = 0;
  unsigned long long llvm_cbe_tmp__187;
  static  unsigned long long aesl_llvm_cbe_1021_count = 0;
  signed short *llvm_cbe_tmp__188;
  static  unsigned long long aesl_llvm_cbe_1022_count = 0;
  unsigned short llvm_cbe_tmp__189;
  static  unsigned long long aesl_llvm_cbe_1023_count = 0;
  signed short *llvm_cbe_tmp__190;
  static  unsigned long long aesl_llvm_cbe_1024_count = 0;
  static  unsigned long long aesl_llvm_cbe_1025_count = 0;
  static  unsigned long long aesl_llvm_cbe_1026_count = 0;
  static  unsigned long long aesl_llvm_cbe_1027_count = 0;
  static  unsigned long long aesl_llvm_cbe_1028_count = 0;
  static  unsigned long long aesl_llvm_cbe_1029_count = 0;
  static  unsigned long long aesl_llvm_cbe_1030_count = 0;
  unsigned int llvm_cbe_tmp__191;
  static  unsigned long long aesl_llvm_cbe_1031_count = 0;
  unsigned long long llvm_cbe_tmp__192;
  static  unsigned long long aesl_llvm_cbe_1032_count = 0;
  signed short *llvm_cbe_tmp__193;
  static  unsigned long long aesl_llvm_cbe_1033_count = 0;
  unsigned short llvm_cbe_tmp__194;
  static  unsigned long long aesl_llvm_cbe_1034_count = 0;
  signed short *llvm_cbe_tmp__195;
  static  unsigned long long aesl_llvm_cbe_1035_count = 0;
  static  unsigned long long aesl_llvm_cbe_1036_count = 0;
  static  unsigned long long aesl_llvm_cbe_1037_count = 0;
  static  unsigned long long aesl_llvm_cbe_1038_count = 0;
  static  unsigned long long aesl_llvm_cbe_1039_count = 0;
  static  unsigned long long aesl_llvm_cbe_1040_count = 0;
  static  unsigned long long aesl_llvm_cbe_1041_count = 0;
  unsigned int llvm_cbe_tmp__196;
  static  unsigned long long aesl_llvm_cbe_1042_count = 0;
  static  unsigned long long aesl_llvm_cbe_1043_count = 0;
  static  unsigned long long aesl_llvm_cbe_1044_count = 0;
  static  unsigned long long aesl_llvm_cbe_1045_count = 0;
  static  unsigned long long aesl_llvm_cbe_1046_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_1047_count = 0;
  static  unsigned long long aesl_llvm_cbe_1048_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @read_data\n");
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ 0, %%0 ], [ %%42, %%.preheader  for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__196);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = shl i32 %%storemerge3, 3, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_952_count);
  llvm_cbe_tmp__155 = (unsigned int )llvm_cbe_storemerge3 << 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__155);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = sext i32 %%storemerge3 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_953_count);
  llvm_cbe_tmp__156 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__156);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sext i32 %%1 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_954_count);
  llvm_cbe_tmp__157 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__155);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__157);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds i16* %%input, i64 %%3, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_955_count);
  llvm_cbe_tmp__158 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__157))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__157));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load i16* %%4, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_956_count);
  llvm_cbe_tmp__159 = (unsigned short )*llvm_cbe_tmp__158;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__159);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 0, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_957_count);
  llvm_cbe_tmp__160 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%5, i16* %%6, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_958_count);
  *llvm_cbe_tmp__160 = llvm_cbe_tmp__159;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__159);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = or i32 %%1, 1, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_964_count);
  llvm_cbe_tmp__161 = (unsigned int )llvm_cbe_tmp__155 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__161);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = sext i32 %%7 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_965_count);
  llvm_cbe_tmp__162 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__161);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__162);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = getelementptr inbounds i16* %%input, i64 %%8, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_966_count);
  llvm_cbe_tmp__163 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__162))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__162));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = load i16* %%9, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_967_count);
  llvm_cbe_tmp__164 = (unsigned short )*llvm_cbe_tmp__163;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__164);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 1, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_968_count);
  llvm_cbe_tmp__165 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )1ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%10, i16* %%11, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_969_count);
  *llvm_cbe_tmp__165 = llvm_cbe_tmp__164;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__164);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = or i32 %%1, 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_975_count);
  llvm_cbe_tmp__166 = (unsigned int )llvm_cbe_tmp__155 | 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__166);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = sext i32 %%12 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_976_count);
  llvm_cbe_tmp__167 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__166);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__167);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds i16* %%input, i64 %%13, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_977_count);
  llvm_cbe_tmp__168 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__167))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__167));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i16* %%14, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_978_count);
  llvm_cbe_tmp__169 = (unsigned short )*llvm_cbe_tmp__168;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__169);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_979_count);
  llvm_cbe_tmp__170 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )2ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )2ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%15, i16* %%16, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_980_count);
  *llvm_cbe_tmp__170 = llvm_cbe_tmp__169;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__169);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = or i32 %%1, 3, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_986_count);
  llvm_cbe_tmp__171 = (unsigned int )llvm_cbe_tmp__155 | 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__171);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = sext i32 %%17 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_987_count);
  llvm_cbe_tmp__172 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__171);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__172);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds i16* %%input, i64 %%18, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_988_count);
  llvm_cbe_tmp__173 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__172))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__172));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = load i16* %%19, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_989_count);
  llvm_cbe_tmp__174 = (unsigned short )*llvm_cbe_tmp__173;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__174);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 3, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_990_count);
  llvm_cbe_tmp__175 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )3ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )3ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%20, i16* %%21, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_991_count);
  *llvm_cbe_tmp__175 = llvm_cbe_tmp__174;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__174);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = or i32 %%1, 4, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_997_count);
  llvm_cbe_tmp__176 = (unsigned int )llvm_cbe_tmp__155 | 4u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__176);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = sext i32 %%22 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_998_count);
  llvm_cbe_tmp__177 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__176);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__177);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = getelementptr inbounds i16* %%input, i64 %%23, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_999_count);
  llvm_cbe_tmp__178 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__177))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__177));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = load i16* %%24, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1000_count);
  llvm_cbe_tmp__179 = (unsigned short )*llvm_cbe_tmp__178;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__179);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 4, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1001_count);
  llvm_cbe_tmp__180 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )4ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )4ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%25, i16* %%26, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1002_count);
  *llvm_cbe_tmp__180 = llvm_cbe_tmp__179;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__179);
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = or i32 %%1, 5, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1008_count);
  llvm_cbe_tmp__181 = (unsigned int )llvm_cbe_tmp__155 | 5u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__181);
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = sext i32 %%27 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1009_count);
  llvm_cbe_tmp__182 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__181);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__182);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = getelementptr inbounds i16* %%input, i64 %%28, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1010_count);
  llvm_cbe_tmp__183 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__182))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__182));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = load i16* %%29, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1011_count);
  llvm_cbe_tmp__184 = (unsigned short )*llvm_cbe_tmp__183;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__184);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 5, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1012_count);
  llvm_cbe_tmp__185 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )5ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )5ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%30, i16* %%31, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1013_count);
  *llvm_cbe_tmp__185 = llvm_cbe_tmp__184;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__184);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = or i32 %%1, 6, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1019_count);
  llvm_cbe_tmp__186 = (unsigned int )llvm_cbe_tmp__155 | 6u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__186);
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = sext i32 %%32 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1020_count);
  llvm_cbe_tmp__187 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__186);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__187);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = getelementptr inbounds i16* %%input, i64 %%33, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1021_count);
  llvm_cbe_tmp__188 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__187))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__187));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = load i16* %%34, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1022_count);
  llvm_cbe_tmp__189 = (unsigned short )*llvm_cbe_tmp__188;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__189);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 6, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1023_count);
  llvm_cbe_tmp__190 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )6ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )6ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%35, i16* %%36, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1024_count);
  *llvm_cbe_tmp__190 = llvm_cbe_tmp__189;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__189);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = or i32 %%1, 7, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1030_count);
  llvm_cbe_tmp__191 = (unsigned int )llvm_cbe_tmp__155 | 7u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__191);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = sext i32 %%37 to i64, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1031_count);
  llvm_cbe_tmp__192 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__191);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__192);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = getelementptr inbounds i16* %%input, i64 %%38, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1032_count);
  llvm_cbe_tmp__193 = (signed short *)(&llvm_cbe_input[(((signed long long )llvm_cbe_tmp__192))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__192));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = load i16* %%39, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1033_count);
  llvm_cbe_tmp__194 = (unsigned short )*llvm_cbe_tmp__193;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__194);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = getelementptr inbounds [8 x i16]* %%buf, i64 %%2, i64 7, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1034_count);
  llvm_cbe_tmp__195 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__156))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__156));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )7ull) < 8 && "Write access out of array 'buf' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%40, i16* %%41, align 2, !dbg !6 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1035_count);
  *llvm_cbe_tmp__195 = llvm_cbe_tmp__194;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__194);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = add nsw i32 %%storemerge3, 1, !dbg !7 for 0x%I64xth hint within @read_data  --> \n", ++aesl_llvm_cbe_1041_count);
  llvm_cbe_tmp__196 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__196&4294967295ull)));
  if (((llvm_cbe_tmp__196&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__197;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__196;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__197:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @read_data}\n");
  return;
}


void write_data(signed short (*llvm_cbe_buf)[8], signed short *llvm_cbe_output) {
  static  unsigned long long aesl_llvm_cbe_1049_count = 0;
  static  unsigned long long aesl_llvm_cbe_1050_count = 0;
  static  unsigned long long aesl_llvm_cbe_1051_count = 0;
  static  unsigned long long aesl_llvm_cbe_1052_count = 0;
  static  unsigned long long aesl_llvm_cbe_1053_count = 0;
  static  unsigned long long aesl_llvm_cbe_1054_count = 0;
  static  unsigned long long aesl_llvm_cbe_1055_count = 0;
  static  unsigned long long aesl_llvm_cbe_1056_count = 0;
  static  unsigned long long aesl_llvm_cbe_1057_count = 0;
  static  unsigned long long aesl_llvm_cbe_1058_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_1059_count = 0;
  static  unsigned long long aesl_llvm_cbe_1060_count = 0;
  static  unsigned long long aesl_llvm_cbe_1061_count = 0;
  static  unsigned long long aesl_llvm_cbe_1062_count = 0;
  static  unsigned long long aesl_llvm_cbe_1063_count = 0;
  unsigned long long llvm_cbe_tmp__198;
  static  unsigned long long aesl_llvm_cbe_1064_count = 0;
  unsigned int llvm_cbe_tmp__199;
  static  unsigned long long aesl_llvm_cbe_1065_count = 0;
  signed short *llvm_cbe_tmp__200;
  static  unsigned long long aesl_llvm_cbe_1066_count = 0;
  unsigned short llvm_cbe_tmp__201;
  static  unsigned long long aesl_llvm_cbe_1067_count = 0;
  unsigned long long llvm_cbe_tmp__202;
  static  unsigned long long aesl_llvm_cbe_1068_count = 0;
  signed short *llvm_cbe_tmp__203;
  static  unsigned long long aesl_llvm_cbe_1069_count = 0;
  static  unsigned long long aesl_llvm_cbe_1070_count = 0;
  static  unsigned long long aesl_llvm_cbe_1071_count = 0;
  static  unsigned long long aesl_llvm_cbe_1072_count = 0;
  static  unsigned long long aesl_llvm_cbe_1073_count = 0;
  static  unsigned long long aesl_llvm_cbe_1074_count = 0;
  static  unsigned long long aesl_llvm_cbe_1075_count = 0;
  signed short *llvm_cbe_tmp__204;
  static  unsigned long long aesl_llvm_cbe_1076_count = 0;
  unsigned short llvm_cbe_tmp__205;
  static  unsigned long long aesl_llvm_cbe_1077_count = 0;
  unsigned int llvm_cbe_tmp__206;
  static  unsigned long long aesl_llvm_cbe_1078_count = 0;
  unsigned long long llvm_cbe_tmp__207;
  static  unsigned long long aesl_llvm_cbe_1079_count = 0;
  signed short *llvm_cbe_tmp__208;
  static  unsigned long long aesl_llvm_cbe_1080_count = 0;
  static  unsigned long long aesl_llvm_cbe_1081_count = 0;
  static  unsigned long long aesl_llvm_cbe_1082_count = 0;
  static  unsigned long long aesl_llvm_cbe_1083_count = 0;
  static  unsigned long long aesl_llvm_cbe_1084_count = 0;
  static  unsigned long long aesl_llvm_cbe_1085_count = 0;
  static  unsigned long long aesl_llvm_cbe_1086_count = 0;
  signed short *llvm_cbe_tmp__209;
  static  unsigned long long aesl_llvm_cbe_1087_count = 0;
  unsigned short llvm_cbe_tmp__210;
  static  unsigned long long aesl_llvm_cbe_1088_count = 0;
  unsigned int llvm_cbe_tmp__211;
  static  unsigned long long aesl_llvm_cbe_1089_count = 0;
  unsigned long long llvm_cbe_tmp__212;
  static  unsigned long long aesl_llvm_cbe_1090_count = 0;
  signed short *llvm_cbe_tmp__213;
  static  unsigned long long aesl_llvm_cbe_1091_count = 0;
  static  unsigned long long aesl_llvm_cbe_1092_count = 0;
  static  unsigned long long aesl_llvm_cbe_1093_count = 0;
  static  unsigned long long aesl_llvm_cbe_1094_count = 0;
  static  unsigned long long aesl_llvm_cbe_1095_count = 0;
  static  unsigned long long aesl_llvm_cbe_1096_count = 0;
  static  unsigned long long aesl_llvm_cbe_1097_count = 0;
  signed short *llvm_cbe_tmp__214;
  static  unsigned long long aesl_llvm_cbe_1098_count = 0;
  unsigned short llvm_cbe_tmp__215;
  static  unsigned long long aesl_llvm_cbe_1099_count = 0;
  unsigned int llvm_cbe_tmp__216;
  static  unsigned long long aesl_llvm_cbe_1100_count = 0;
  unsigned long long llvm_cbe_tmp__217;
  static  unsigned long long aesl_llvm_cbe_1101_count = 0;
  signed short *llvm_cbe_tmp__218;
  static  unsigned long long aesl_llvm_cbe_1102_count = 0;
  static  unsigned long long aesl_llvm_cbe_1103_count = 0;
  static  unsigned long long aesl_llvm_cbe_1104_count = 0;
  static  unsigned long long aesl_llvm_cbe_1105_count = 0;
  static  unsigned long long aesl_llvm_cbe_1106_count = 0;
  static  unsigned long long aesl_llvm_cbe_1107_count = 0;
  static  unsigned long long aesl_llvm_cbe_1108_count = 0;
  signed short *llvm_cbe_tmp__219;
  static  unsigned long long aesl_llvm_cbe_1109_count = 0;
  unsigned short llvm_cbe_tmp__220;
  static  unsigned long long aesl_llvm_cbe_1110_count = 0;
  unsigned int llvm_cbe_tmp__221;
  static  unsigned long long aesl_llvm_cbe_1111_count = 0;
  unsigned long long llvm_cbe_tmp__222;
  static  unsigned long long aesl_llvm_cbe_1112_count = 0;
  signed short *llvm_cbe_tmp__223;
  static  unsigned long long aesl_llvm_cbe_1113_count = 0;
  static  unsigned long long aesl_llvm_cbe_1114_count = 0;
  static  unsigned long long aesl_llvm_cbe_1115_count = 0;
  static  unsigned long long aesl_llvm_cbe_1116_count = 0;
  static  unsigned long long aesl_llvm_cbe_1117_count = 0;
  static  unsigned long long aesl_llvm_cbe_1118_count = 0;
  static  unsigned long long aesl_llvm_cbe_1119_count = 0;
  signed short *llvm_cbe_tmp__224;
  static  unsigned long long aesl_llvm_cbe_1120_count = 0;
  unsigned short llvm_cbe_tmp__225;
  static  unsigned long long aesl_llvm_cbe_1121_count = 0;
  unsigned int llvm_cbe_tmp__226;
  static  unsigned long long aesl_llvm_cbe_1122_count = 0;
  unsigned long long llvm_cbe_tmp__227;
  static  unsigned long long aesl_llvm_cbe_1123_count = 0;
  signed short *llvm_cbe_tmp__228;
  static  unsigned long long aesl_llvm_cbe_1124_count = 0;
  static  unsigned long long aesl_llvm_cbe_1125_count = 0;
  static  unsigned long long aesl_llvm_cbe_1126_count = 0;
  static  unsigned long long aesl_llvm_cbe_1127_count = 0;
  static  unsigned long long aesl_llvm_cbe_1128_count = 0;
  static  unsigned long long aesl_llvm_cbe_1129_count = 0;
  static  unsigned long long aesl_llvm_cbe_1130_count = 0;
  signed short *llvm_cbe_tmp__229;
  static  unsigned long long aesl_llvm_cbe_1131_count = 0;
  unsigned short llvm_cbe_tmp__230;
  static  unsigned long long aesl_llvm_cbe_1132_count = 0;
  unsigned int llvm_cbe_tmp__231;
  static  unsigned long long aesl_llvm_cbe_1133_count = 0;
  unsigned long long llvm_cbe_tmp__232;
  static  unsigned long long aesl_llvm_cbe_1134_count = 0;
  signed short *llvm_cbe_tmp__233;
  static  unsigned long long aesl_llvm_cbe_1135_count = 0;
  static  unsigned long long aesl_llvm_cbe_1136_count = 0;
  static  unsigned long long aesl_llvm_cbe_1137_count = 0;
  static  unsigned long long aesl_llvm_cbe_1138_count = 0;
  static  unsigned long long aesl_llvm_cbe_1139_count = 0;
  static  unsigned long long aesl_llvm_cbe_1140_count = 0;
  static  unsigned long long aesl_llvm_cbe_1141_count = 0;
  signed short *llvm_cbe_tmp__234;
  static  unsigned long long aesl_llvm_cbe_1142_count = 0;
  unsigned short llvm_cbe_tmp__235;
  static  unsigned long long aesl_llvm_cbe_1143_count = 0;
  unsigned int llvm_cbe_tmp__236;
  static  unsigned long long aesl_llvm_cbe_1144_count = 0;
  unsigned long long llvm_cbe_tmp__237;
  static  unsigned long long aesl_llvm_cbe_1145_count = 0;
  signed short *llvm_cbe_tmp__238;
  static  unsigned long long aesl_llvm_cbe_1146_count = 0;
  static  unsigned long long aesl_llvm_cbe_1147_count = 0;
  static  unsigned long long aesl_llvm_cbe_1148_count = 0;
  static  unsigned long long aesl_llvm_cbe_1149_count = 0;
  static  unsigned long long aesl_llvm_cbe_1150_count = 0;
  static  unsigned long long aesl_llvm_cbe_1151_count = 0;
  static  unsigned long long aesl_llvm_cbe_1152_count = 0;
  unsigned int llvm_cbe_tmp__239;
  static  unsigned long long aesl_llvm_cbe_1153_count = 0;
  static  unsigned long long aesl_llvm_cbe_1154_count = 0;
  static  unsigned long long aesl_llvm_cbe_1155_count = 0;
  static  unsigned long long aesl_llvm_cbe_1156_count = 0;
  static  unsigned long long aesl_llvm_cbe_1157_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_1158_count = 0;
  static  unsigned long long aesl_llvm_cbe_1159_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @write_data\n");
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ 0, %%0 ], [ %%42, %%.preheader  for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__239);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = sext i32 %%storemerge3 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1063_count);
  llvm_cbe_tmp__198 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__198);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = shl i32 %%storemerge3, 3, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1064_count);
  llvm_cbe_tmp__199 = (unsigned int )llvm_cbe_storemerge3 << 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__199);
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 0, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1065_count);
  llvm_cbe_tmp__200 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )0ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load i16* %%3, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1066_count);
  llvm_cbe_tmp__201 = (unsigned short )*llvm_cbe_tmp__200;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__201);
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = sext i32 %%2 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1067_count);
  llvm_cbe_tmp__202 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__199);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__202);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = getelementptr inbounds i16* %%output, i64 %%5, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1068_count);
  llvm_cbe_tmp__203 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__202))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__202));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%4, i16* %%6, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1069_count);
  *llvm_cbe_tmp__203 = llvm_cbe_tmp__201;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__201);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 1, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1075_count);
  llvm_cbe_tmp__204 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )1ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load i16* %%7, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1076_count);
  llvm_cbe_tmp__205 = (unsigned short )*llvm_cbe_tmp__204;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__205);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = or i32 %%2, 1, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1077_count);
  llvm_cbe_tmp__206 = (unsigned int )llvm_cbe_tmp__199 | 1u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__206);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sext i32 %%9 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1078_count);
  llvm_cbe_tmp__207 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__206);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__207);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds i16* %%output, i64 %%10, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1079_count);
  llvm_cbe_tmp__208 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__207))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__207));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%8, i16* %%11, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1080_count);
  *llvm_cbe_tmp__208 = llvm_cbe_tmp__205;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__205);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1086_count);
  llvm_cbe_tmp__209 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )2ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )2ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = load i16* %%12, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1087_count);
  llvm_cbe_tmp__210 = (unsigned short )*llvm_cbe_tmp__209;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__210);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = or i32 %%2, 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1088_count);
  llvm_cbe_tmp__211 = (unsigned int )llvm_cbe_tmp__199 | 2u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__211);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = sext i32 %%14 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1089_count);
  llvm_cbe_tmp__212 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__211);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__212);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds i16* %%output, i64 %%15, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1090_count);
  llvm_cbe_tmp__213 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__212))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__212));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%13, i16* %%16, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1091_count);
  *llvm_cbe_tmp__213 = llvm_cbe_tmp__210;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__210);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 3, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1097_count);
  llvm_cbe_tmp__214 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )3ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )3ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = load i16* %%17, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1098_count);
  llvm_cbe_tmp__215 = (unsigned short )*llvm_cbe_tmp__214;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__215);
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = or i32 %%2, 3, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1099_count);
  llvm_cbe_tmp__216 = (unsigned int )llvm_cbe_tmp__199 | 3u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__216);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = sext i32 %%19 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1100_count);
  llvm_cbe_tmp__217 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__216);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__217);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds i16* %%output, i64 %%20, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1101_count);
  llvm_cbe_tmp__218 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__217))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__217));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%18, i16* %%21, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1102_count);
  *llvm_cbe_tmp__218 = llvm_cbe_tmp__215;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__215);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 4, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1108_count);
  llvm_cbe_tmp__219 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )4ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )4ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load i16* %%22, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1109_count);
  llvm_cbe_tmp__220 = (unsigned short )*llvm_cbe_tmp__219;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__220);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = or i32 %%2, 4, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1110_count);
  llvm_cbe_tmp__221 = (unsigned int )llvm_cbe_tmp__199 | 4u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__221);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = sext i32 %%24 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1111_count);
  llvm_cbe_tmp__222 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__221);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__222);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = getelementptr inbounds i16* %%output, i64 %%25, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1112_count);
  llvm_cbe_tmp__223 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__222))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__222));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%23, i16* %%26, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1113_count);
  *llvm_cbe_tmp__223 = llvm_cbe_tmp__220;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__220);
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 5, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1119_count);
  llvm_cbe_tmp__224 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )5ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )5ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = load i16* %%27, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1120_count);
  llvm_cbe_tmp__225 = (unsigned short )*llvm_cbe_tmp__224;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__225);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = or i32 %%2, 5, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1121_count);
  llvm_cbe_tmp__226 = (unsigned int )llvm_cbe_tmp__199 | 5u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__226);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = sext i32 %%29 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1122_count);
  llvm_cbe_tmp__227 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__226);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__227);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = getelementptr inbounds i16* %%output, i64 %%30, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1123_count);
  llvm_cbe_tmp__228 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__227))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__227));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%28, i16* %%31, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1124_count);
  *llvm_cbe_tmp__228 = llvm_cbe_tmp__225;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__225);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 6, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1130_count);
  llvm_cbe_tmp__229 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )6ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )6ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i16* %%32, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1131_count);
  llvm_cbe_tmp__230 = (unsigned short )*llvm_cbe_tmp__229;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__230);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = or i32 %%2, 6, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1132_count);
  llvm_cbe_tmp__231 = (unsigned int )llvm_cbe_tmp__199 | 6u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__231);
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = sext i32 %%34 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1133_count);
  llvm_cbe_tmp__232 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__231);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__232);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = getelementptr inbounds i16* %%output, i64 %%35, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1134_count);
  llvm_cbe_tmp__233 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__232))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__232));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%33, i16* %%36, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1135_count);
  *llvm_cbe_tmp__233 = llvm_cbe_tmp__230;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__230);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds [8 x i16]* %%buf, i64 %%1, i64 7, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1141_count);
  llvm_cbe_tmp__234 = (signed short *)(&llvm_cbe_buf[(((signed long long )llvm_cbe_tmp__198))
#ifdef AESL_BC_SIM
 % 8
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__198));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )7ull) < 8)) fprintf(stderr, "%s:%d: warning: Read access out of array 'buf' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = load i16* %%37, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1142_count);
  llvm_cbe_tmp__235 = (unsigned short )*llvm_cbe_tmp__234;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__235);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = or i32 %%2, 7, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1143_count);
  llvm_cbe_tmp__236 = (unsigned int )llvm_cbe_tmp__199 | 7u;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__236);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = sext i32 %%39 to i64, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1144_count);
  llvm_cbe_tmp__237 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__236);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__237);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = getelementptr inbounds i16* %%output, i64 %%40, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1145_count);
  llvm_cbe_tmp__238 = (signed short *)(&llvm_cbe_output[(((signed long long )llvm_cbe_tmp__237))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__237));
}
if (AESL_DEBUG_TRACE)
printf("\n  store i16 %%38, i16* %%41, align 2, !dbg !6 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1146_count);
  *llvm_cbe_tmp__238 = llvm_cbe_tmp__235;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__235);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = add nsw i32 %%storemerge3, 1, !dbg !7 for 0x%I64xth hint within @write_data  --> \n", ++aesl_llvm_cbe_1152_count);
  llvm_cbe_tmp__239 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__239&4294967295ull)));
  if (((llvm_cbe_tmp__239&4294967295U) == (8u&4294967295U))) {
    goto llvm_cbe_tmp__240;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__239;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__240:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @write_data}\n");
  return;
}


void dct(signed short *llvm_cbe_input, signed short *llvm_cbe_output) {
  static  unsigned long long aesl_llvm_cbe_buf_2d_in_count = 0;
  signed short llvm_cbe_buf_2d_in[8][8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_buf_2d_out_count = 0;
  signed short llvm_cbe_buf_2d_out[8][8];    /* Address-exposed local */
  static  unsigned long long aesl_llvm_cbe_1160_count = 0;
  static  unsigned long long aesl_llvm_cbe_1161_count = 0;
  static  unsigned long long aesl_llvm_cbe_1162_count = 0;
  static  unsigned long long aesl_llvm_cbe_1163_count = 0;
  static  unsigned long long aesl_llvm_cbe_1164_count = 0;
  static  unsigned long long aesl_llvm_cbe_1165_count = 0;
  static  unsigned long long aesl_llvm_cbe_1166_count = 0;
  signed short (*llvm_cbe_tmp__241)[8];
  static  unsigned long long aesl_llvm_cbe_1167_count = 0;
  static  unsigned long long aesl_llvm_cbe_1168_count = 0;
  signed short (*llvm_cbe_tmp__242)[8];
  static  unsigned long long aesl_llvm_cbe_1169_count = 0;
  static  unsigned long long aesl_llvm_cbe_1170_count = 0;
  static  unsigned long long aesl_llvm_cbe_1171_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @dct\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = getelementptr inbounds [8 x [8 x i16]]* %%buf_2d_in, i64 0, i64 0, !dbg !7 for 0x%I64xth hint within @dct  --> \n", ++aesl_llvm_cbe_1166_count);
  llvm_cbe_tmp__241 = (signed short (*)[8])(&llvm_cbe_buf_2d_in[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @read_data(i16* %%input, [8 x i16]* %%1), !dbg !7 for 0x%I64xth hint within @dct  --> \n", ++aesl_llvm_cbe_1167_count);
  read_data((signed short *)llvm_cbe_input, llvm_cbe_tmp__241);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds [8 x [8 x i16]]* %%buf_2d_out, i64 0, i64 0, !dbg !7 for 0x%I64xth hint within @dct  --> \n", ++aesl_llvm_cbe_1168_count);
  llvm_cbe_tmp__242 = (signed short (*)[8])(&llvm_cbe_buf_2d_out[(((signed long long )0ull))
#ifdef AESL_BC_SIM
 % 8
#endif
]);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @dct_2d([8 x i16]* %%1, [8 x i16]* %%2), !dbg !7 for 0x%I64xth hint within @dct  --> \n", ++aesl_llvm_cbe_1169_count);
  dct_2d(llvm_cbe_tmp__241, llvm_cbe_tmp__242);
if (AESL_DEBUG_TRACE) {
}
if (AESL_DEBUG_TRACE)
printf("\n  call void @write_data([8 x i16]* %%2, i16* %%output), !dbg !6 for 0x%I64xth hint within @dct  --> \n", ++aesl_llvm_cbe_1170_count);
  write_data(llvm_cbe_tmp__242, (signed short *)llvm_cbe_output);
if (AESL_DEBUG_TRACE) {
}
  if (AESL_DEBUG_TRACE)
      printf("\nEND @dct}\n");
  return;
}

