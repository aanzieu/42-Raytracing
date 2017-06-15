#!/bin/bash



### Set initial time of file
#! _BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/FILE.c`

HANDLERS_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/event_handler.c`
KEYS_HANDLER_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/keys_handler.c`
MAIN_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/main.c`
FREE_MEMORY_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/free_memory.c`
RENDER_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/render.c`
RAY_TRACER_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/ray_tracer.cu`
CYLINDER_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/cylinder.cu`
CUDA_BEFORE_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/cuda/cudasrc/gpu_rtv1.cu`



while true    
do
#! _AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/FILE.c`
   HANDLERS_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/event_handler.c`
   KEYS_HANDLER_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/keys_handler.c`   
   MAIN_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/main.c`
   FREE_MEMORY_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/free_memory.c`
   RENDER_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/render.c`
   RAY_TRACER_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/ray_tracer.cu`
   CYLINDER_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/cylinder.cu`
	CUDA_AFTER_TIME=`stat -f "%Sm" -t "%Y%m%dT%H%M%S" ./srcs/cuda/cudasrc/gpu_rtv1.cu`
   
   
   
#! || ("$_BEFORE_TIME" != "$_AFTER_TIME")
   if [[ ("$HANDLERS_BEFORE_TIME" != "$HANDLERS_AFTER_TIME" ) || ("$KEYS_HANDLER_BEFORE_TIME" != "$KEYS_HANDLER_AFTER_TIME" ) || ("$MAIN_BEFORE_TIME" != "$MAIN_AFTER_TIME") || ("$FREE_MEMORY_BEFORE_TIME" != "$FREE_MEMORY_AFTER_TIME") || ("$RENDER_BEFORE_TIME" != "$RENDER_AFTER_TIME") 
   || ("$RAY_TRACER_BEFORE_TIME" != "$RAY_TRACER_AFTER_TIME") || ("$CYLINDER_BEFORE_TIME" != "$CYLINDER_AFTER_TIME") || ("$CUDA_BEFORE_TIME" != "$CUDA_AFTER_TIME")]]
   then    
       make run 
       #norminette includes/*.h
       #norminette srcs/*.c
#! _BEFORE_TIME=$ _AFTER_TIME	   
       HANDLERS_BEFORE_TIME=$HANDLERS_AFTER_TIME
       KEYS_HANDLER_BEFORE_TIME=$KEYS_HANDLER_AFTER_TIME       
       MAIN_BEFORE_TIME=$MAIN_AFTER_TIME
       FREE_MEMORY_BEFORE_TIME=$FREE_MEMORY_AFTER_TIME
       RENDER_BEFORE_TIME=$RENDER_AFTER_TIME       
       RAY_TRACER_BEFORE_TIME=$RAY_TRACER_AFTER_TIME
	   CYLINDER_BEFORE_TIME=$CYLINDER_AFTER_TIME
	   CUDA_BEFORE_TIME=$CUDA_AFTER_TIME
   fi
   sleep 1
done