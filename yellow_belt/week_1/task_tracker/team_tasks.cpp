#include <string>
#include <map>

using namespace std;

class TeamTasks {
public:
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return person_to_tasks_.at(person);
  }

  void AddNewTask(const string& person) {
    ++person_to_tasks_[person][TaskStatus::NEW];
  }

  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count) {
    if (person_to_tasks_.count(person) != 0) {
      task_count = min(task_count, GetPersonUndoneTaskCount(person));
      TasksInfo updated_tasks, untouched_tasks = person_to_tasks_[person];
      TasksInfo new_tasks = person_to_tasks_[person];
      int to_update;
      for (auto& i : person_to_tasks_[person]) {
        to_update = min(task_count, i.second);
        new_tasks[i.first] -= to_update;
        if (new_tasks[i.first] == 0) {
          new_tasks.erase(i.first);
        }
        untouched_tasks[i.first] -= to_update;
        if (untouched_tasks[i.first] == 0) {
          untouched_tasks.erase(i.first);
        }
        switch (i.first) {
          case TaskStatus::NEW:
            new_tasks[TaskStatus::IN_PROGRESS] += to_update;
            updated_tasks[TaskStatus::IN_PROGRESS] += to_update;
            break;
          case TaskStatus::IN_PROGRESS:
            new_tasks[TaskStatus::TESTING] += to_update;
            updated_tasks[TaskStatus::TESTING] += to_update;
            break;
          case TaskStatus::TESTING:
            new_tasks[TaskStatus::DONE] += to_update;
            updated_tasks[TaskStatus::DONE] += to_update;
            break;
          case TaskStatus::DONE:
            break;
        }
        task_count -= to_update;
        if (task_count == 0) {
          break;
        }
      }
      person_to_tasks_[person] = new_tasks;
      untouched_tasks.erase(TaskStatus::DONE);
      return tie(updated_tasks, untouched_tasks);
    } else {
      return tuple<TasksInfo, TasksInfo>();
    }
  }

private:
  map<string, TasksInfo> person_to_tasks_;

  int GetPersonUndoneTaskCount(const string& person) const {
    int count = 0;
    if (person_to_tasks_.count(person) != 0) {
      TasksInfo tasks_info = GetPersonTasksInfo(person);
      count += tasks_info[TaskStatus::NEW];
      count += tasks_info[TaskStatus::IN_PROGRESS];
      count += tasks_info[TaskStatus::TESTING];
    }
    return count;
  }
};
