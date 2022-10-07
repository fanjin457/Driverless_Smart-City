export MIOPEN_DEBUG_DISABLE_FIND_DB=1
export MIOPEN_DEBUG_CONV_WINOGRAD=0 
export MIOPEN_DEBUG_CONV_IMPLICIT_GEMM=0
export HSA_USERPTR_FOR_PAGED_MEM=0
export MIOPEN_SYSTEM_DB_PATH=/temp/pytorch-miopen-2.8
export ROCBLAS_DEVICE_MEMORY_SIZE=128M

export LD_LIBRARY_PATH=/public/home/achrbqpmd9/anaconda3/envs/pytorch-1.9/lib/:/public/software/compiler/rocm/rocm-4.0.1/rocblas/lib/:$LD_LIBRARY_PATH

# Edit to locate your dataset
DTU_TESTING="/public/home/achrbqpmd9/datasets/xinhaoshan/"

batch=1
d=512
interval_scale=0.4
inverse_depth=False
ckpt=./checkpoints/pretrained/model_release.ckpt

CUDA_VISIBLE_DEVICES=0 python -u eval.py \
        --dataset=data_eval_transform \
        --batch_size=${batch} \
        --inverse_depth=${inverse_depth} \
        --numdepth=$d \
        --interval_scale=$interval_scale \
        --max_h=500 \
        --max_w=800 \
        --image_scale=1.0 \
        --testpath=$DTU_TESTING \
        --testlist=lists/zg_pf/test.txt \
        --loadckpt=$ckpt \
        --outdir=./outputs_xinhaoshan | tee -a ./log.txt
