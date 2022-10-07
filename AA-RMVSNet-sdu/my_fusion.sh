export MIOPEN_DEBUG_DISABLE_FIND_DB=1
export MIOPEN_DEBUG_CONV_WINOGRAD=0 
export MIOPEN_DEBUG_CONV_IMPLICIT_GEMM=0
export HSA_USERPTR_FOR_PAGED_MEM=0
export MIOPEN_SYSTEM_DB_PATH=/temp/pytorch-miopen-2.8
export ROCBLAS_DEVICE_MEMORY_SIZE=128M

export LD_LIBRARY_PATH=/public/home/achrbqpmd9/anaconda3/envs/pytorch101_python36//lib/:/public/software/compiler/rocm/rocm-4.0.1/rocblas/lib/:$LD_LIBRARY_PATH

# Edit to locate your dataset
DTU_TESTING="/public/home/achrbqpmd9/datasets/xinhaoshan/"

testlist=./lists/zg_pf/test.txt
outdir=./outputs_xinhaoshan/pretrained_model_release.ckpt/
test_dataset=dtu
python fusion.py --testpath=$DTU_TESTING \
                    --testlist=$testlist \
                    --outdir=$outdir \
                    --test_dataset=$test_dataset  | tee -a ./log_fusion.txt
