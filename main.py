from typing import Union, Annotated

from fastapi import FastAPI, BackgroundTasks, File, UploadFile
from fastapi.responses import JSONResponse
import subprocess
import uuid

app = FastAPI()

# TODO get the cmake env variable for home
exe_path = "/mnt/d/fichiers_pa/dev_ubuntu/MosaicGiphyCpp/build/main"

# Task storage for checking status
task_status = {}


@app.post("/process-image/")
async def process_image(file: UploadFile, background_tasks: BackgroundTasks):
    task_id = str(uuid.uuid4())

    task_status[task_id] = "processing"
    print('file : ', file.filename)
    print("content-type : ", file.content_type)
    
    # save the file locally and run script wtih the file

    background_tasks.add_task(process_image_task, task_id)

    return JSONResponse({"task_id": task_id, "status": "processing"})


def process_image_task(task_id: str):
    """Background task to process image with C++ .exe"""
    # Execute the C++ application
    command = [exe_path]
    subprocess.run(command)

    # After the process, update the task status
    task_status[task_id] = "completed"


@app.get("/check-status/{task_id}")
async def check_status(task_id: str):
    """function to check the status of the running task

    Args:
        task_id (str): ID of the current task

    Returns:
        JSONResponse: JOSNResponse with task_id and status
    """
    status = task_status.get(task_id, "not found")
    if status == "completed":
        return "finished !!!"
    return JSONResponse({"task_id": task_id, "status": status})
