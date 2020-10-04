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

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
void foo(signed int (*llvm_cbe_in1)[10], signed int (*llvm_cbe_in2)[10], signed int (*llvm_cbe_out)[10]);


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

void foo(signed int (*llvm_cbe_in1)[10], signed int (*llvm_cbe_in2)[10], signed int (*llvm_cbe_out)[10]) {
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
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge3_count = 0;
  unsigned int llvm_cbe_storemerge3;
  unsigned int llvm_cbe_storemerge3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  unsigned long long llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  signed int *llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  signed int *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  unsigned int llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  signed int *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  signed int *llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  signed int *llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  unsigned int llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  unsigned int llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  signed int *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  signed int *llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  signed int *llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  unsigned int llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  signed int *llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  signed int *llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  unsigned int llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  signed int *llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  unsigned int llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  signed int *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  signed int *llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  unsigned int llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  signed int *llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  unsigned int llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  signed int *llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  signed int *llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  unsigned int llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  signed int *llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  signed int *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  signed int *llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  signed int *llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  unsigned int llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  unsigned int llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  signed int *llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  signed int *llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  unsigned int llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  signed int *llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  signed int *llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  signed int *llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  signed int *llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  unsigned int llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned int llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  signed int *llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  signed int *llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  unsigned int llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  signed int *llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  unsigned int llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  signed int *llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  unsigned int llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @foo\n");
  llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe__2e_preheader;

  do {     /* Syntactic loop '.preheader' to make GCC happy */
llvm_cbe__2e_preheader:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge3 = phi i32 [ 0, %%0 ], [ %%62, %%.preheader  for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_storemerge3_count);
  llvm_cbe_storemerge3 = (unsigned int )llvm_cbe_storemerge3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge3 = 0x%X",llvm_cbe_storemerge3);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__62);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = sext i32 %%storemerge3 to i64, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_19_count);
  llvm_cbe_tmp__1 = (unsigned long long )((signed long long )(signed int )llvm_cbe_storemerge3);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__1);
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 0, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__2 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )0ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = load i32* %%2, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_21_count);
  llvm_cbe_tmp__3 = (unsigned int )*llvm_cbe_tmp__2;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 0, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_22_count);
  llvm_cbe_tmp__4 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )0ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load i32* %%4, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_tmp__5 = (unsigned int )*llvm_cbe_tmp__4;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add nsw i32 %%5, %%3, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__6 = (unsigned int )((unsigned int )(llvm_cbe_tmp__5&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__3&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__6&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 0, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__7 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )0ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )0ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%6, i32* %%7, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_26_count);
  *llvm_cbe_tmp__7 = llvm_cbe_tmp__6;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 1, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__8 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )1ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load i32* %%8, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__9 = (unsigned int )*llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 1, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__10 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )1ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load i32* %%10, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__11 = (unsigned int )*llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = add nsw i32 %%11, %%9, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__12 = (unsigned int )((unsigned int )(llvm_cbe_tmp__11&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__9&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__12&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 1, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_38_count);
  llvm_cbe_tmp__13 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )1ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )1ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%12, i32* %%13, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_39_count);
  *llvm_cbe_tmp__13 = llvm_cbe_tmp__12;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 2, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__14 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )2ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )2ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = load i32* %%14, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__15 = (unsigned int )*llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 2, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__16 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )2ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )2ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = load i32* %%16, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__17 = (unsigned int )*llvm_cbe_tmp__16;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__17);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = add nsw i32 %%17, %%15, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__18 = (unsigned int )((unsigned int )(llvm_cbe_tmp__17&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__15&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__18&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 2, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__19 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )2ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )2ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%18, i32* %%19, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_52_count);
  *llvm_cbe_tmp__19 = llvm_cbe_tmp__18;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 3, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__20 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )3ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )3ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = load i32* %%20, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_60_count);
  llvm_cbe_tmp__21 = (unsigned int )*llvm_cbe_tmp__20;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 3, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_61_count);
  llvm_cbe_tmp__22 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )3ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )3ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = load i32* %%22, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__23 = (unsigned int )*llvm_cbe_tmp__22;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add nsw i32 %%23, %%21, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__24 = (unsigned int )((unsigned int )(llvm_cbe_tmp__23&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__21&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__24&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 3, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_64_count);
  llvm_cbe_tmp__25 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )3ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )3ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%24, i32* %%25, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_65_count);
  *llvm_cbe_tmp__25 = llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__26 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )4ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )4ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = load i32* %%26, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__27 = (unsigned int )*llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__28 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )4ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )4ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = load i32* %%28, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__29 = (unsigned int )*llvm_cbe_tmp__28;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = add nsw i32 %%29, %%27, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__30 = (unsigned int )((unsigned int )(llvm_cbe_tmp__29&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__27&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__30&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_77_count);
  llvm_cbe_tmp__31 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )4ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )4ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%30, i32* %%31, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_78_count);
  *llvm_cbe_tmp__31 = llvm_cbe_tmp__30;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 5, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__32 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )5ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )5ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = load i32* %%32, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__33 = (unsigned int )*llvm_cbe_tmp__32;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__33);
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 5, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__34 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )5ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )5ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = load i32* %%34, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__35 = (unsigned int )*llvm_cbe_tmp__34;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = add nsw i32 %%35, %%33, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__36 = (unsigned int )((unsigned int )(llvm_cbe_tmp__35&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__33&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__36&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 5, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__37 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )5ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )5ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%36, i32* %%37, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_91_count);
  *llvm_cbe_tmp__37 = llvm_cbe_tmp__36;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 6, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_98_count);
  llvm_cbe_tmp__38 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )6ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )6ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = load i32* %%38, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_99_count);
  llvm_cbe_tmp__39 = (unsigned int )*llvm_cbe_tmp__38;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 6, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__40 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )6ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )6ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = load i32* %%40, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__41 = (unsigned int )*llvm_cbe_tmp__40;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__41);
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = add nsw i32 %%41, %%39, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__42 = (unsigned int )((unsigned int )(llvm_cbe_tmp__41&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__39&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__42&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 6, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_103_count);
  llvm_cbe_tmp__43 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )6ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )6ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%42, i32* %%43, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_104_count);
  *llvm_cbe_tmp__43 = llvm_cbe_tmp__42;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 7, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__44 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )7ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = load i32* %%44, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_112_count);
  llvm_cbe_tmp__45 = (unsigned int )*llvm_cbe_tmp__44;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__45);
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 7, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__46 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )7ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = load i32* %%46, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__47 = (unsigned int )*llvm_cbe_tmp__46;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = add nsw i32 %%47, %%45, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__48 = (unsigned int )((unsigned int )(llvm_cbe_tmp__47&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__45&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__48&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 7, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_116_count);
  llvm_cbe_tmp__49 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )7ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )7ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%48, i32* %%49, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_117_count);
  *llvm_cbe_tmp__49 = llvm_cbe_tmp__48;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__48);
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 8, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__50 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )8ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )8ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = load i32* %%50, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__51 = (unsigned int )*llvm_cbe_tmp__50;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 8, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__52 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )8ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )8ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = load i32* %%52, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__53 = (unsigned int )*llvm_cbe_tmp__52;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__53);
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = add nsw i32 %%53, %%51, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__54 = (unsigned int )((unsigned int )(llvm_cbe_tmp__53&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__51&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__54&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 8, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_129_count);
  llvm_cbe_tmp__55 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )8ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )8ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%54, i32* %%55, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_130_count);
  *llvm_cbe_tmp__55 = llvm_cbe_tmp__54;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = getelementptr inbounds [10 x i32]* %%in1, i64 %%1, i64 9, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__56 = (signed int *)(&llvm_cbe_in1[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )9ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )9ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in1' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = load i32* %%56, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__57 = (unsigned int )*llvm_cbe_tmp__56;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__57);
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = getelementptr inbounds [10 x i32]* %%in2, i64 %%1, i64 9, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__58 = (signed int *)(&llvm_cbe_in2[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )9ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  if (!(((signed long long )9ull) < 10)) fprintf(stderr, "%s:%d: warning: Read access out of array 'in2' bound?\n", __FILE__, __LINE__);

#endif
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = load i32* %%58, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_140_count);
  llvm_cbe_tmp__59 = (unsigned int )*llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = add nsw i32 %%59, %%57, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__60 = (unsigned int )((unsigned int )(llvm_cbe_tmp__59&4294967295ull)) + ((unsigned int )(llvm_cbe_tmp__57&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__60&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = getelementptr inbounds [10 x i32]* %%out, i64 %%1, i64 9, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__61 = (signed int *)(&llvm_cbe_out[(((signed long long )llvm_cbe_tmp__1))
#ifdef AESL_BC_SIM
 % 10
#endif
][(((signed long long )9ull))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__1));
}

#ifdef AESL_BC_SIM
  assert(((signed long long )9ull) < 10 && "Write access out of array 'out' bound?");

#endif
if (AESL_DEBUG_TRACE)
printf("\n  store i32 %%60, i32* %%61, align 4, !dbg !2 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_143_count);
  *llvm_cbe_tmp__61 = llvm_cbe_tmp__60;
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = add nsw i32 %%storemerge3, 1, !dbg !3 for 0x%I64xth hint within @foo  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__62 = (unsigned int )((unsigned int )(llvm_cbe_storemerge3&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__62&4294967295ull)));
  if (((llvm_cbe_tmp__62&4294967295U) == (10u&4294967295U))) {
    goto llvm_cbe_tmp__63;
  } else {
    llvm_cbe_storemerge3__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__62;   /* for PHI node */
    goto llvm_cbe__2e_preheader;
  }

  } while (1); /* end of syntactic loop '.preheader' */
llvm_cbe_tmp__63:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @foo}\n");
  return;
}

