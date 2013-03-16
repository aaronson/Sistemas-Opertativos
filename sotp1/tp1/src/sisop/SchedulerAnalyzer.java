package sisop;

import java.util.Iterator;

/**
 * Permite extraer estadisticas de la planificacion.
 * Esta clase es invocada una vez finalizada
 * la planificacion.
 */
class SchedulerAnalyzer {

  private TaskSet task_set;

  /**
   * Construye un nuevo analizador usando
   * un TaskSet producto de una planificacion
   * terminada
   */
  public SchedulerAnalyzer(TaskSet task_set) { 
    this.task_set = task_set;
  }

  /**
   * Retorna el waiting time promedio de 
   * una tarea.
   */
  public int get_avg_wtime() {
    int acum=0;
    int cant = task_set.size();
    Iterator<Task> it = task_set.iterator();
    while(it.hasNext()){
    	Task tarea = it.next();
    	acum+= tarea.wtime;
    }
    return (acum/cant);
  }

}
