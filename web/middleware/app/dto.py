import json

class TaskManager:
    """ TaskManager class """
    def __init__(self):
        self.CACHE_DIR = "tasks.json"
        with open(self.CACHE_DIR, 'w') as f:
            f.write(json.dumps({}))

    def get_task_status(self, taskId):
        """ Get the status of a task """
        tasks = {}
        with open(self.CACHE_DIR) as f:
            tasks = json.loads(f.read())
            return tasks.get(taskId)

    def update_task_status(self, taskId, status):
        """ Update the status of a task """
        tasks = {}
        with open(self.CACHE_DIR) as f:
            tasks = json.loads(f.read())
        tasks[taskId] = status
        with open(self.CACHE_DIR, 'w') as f:
            f.write(json.dumps(tasks))
    
