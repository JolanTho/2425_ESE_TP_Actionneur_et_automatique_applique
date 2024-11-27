#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct {
    float kp;        // Gain proportionnel
    float ki;        // Gain intégral
    float kd;        // Gain dérivé
    float prevError; // Erreur précédente
    float integral;  // Accumulateur pour le terme intégral
} PIDController;

/**
 * @brief Initialise un contrôleur PID.
 *
 * @param kp Gain proportionnel.
 * @param ki Gain intégral.
 * @param kd Gain dérivé.
 * @return PIDController Initialisé.
 */
PIDController pid_init(float kp, float ki, float kd);

/**
 * @brief Calcule l'alpha basé sur la vitesse mesurée et la consigne.
 *
 * @param pid Le contrôleur PID.
 * @param setpoint La consigne de vitesse (-3000 à 3000).
 * @param measured La vitesse mesurée (-200 à 200).
 * @param deltaTime Intervalle de temps (en secondes).
 * @return float Alpha (0-100) pour le contrôle PWM.
 */
float pid_compute(PIDController *pid, float setpoint, float measured, float deltaTime);

#endif // PID_CONTROLLER_H
