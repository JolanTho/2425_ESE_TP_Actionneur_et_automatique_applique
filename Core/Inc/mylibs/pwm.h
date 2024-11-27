#ifndef INC_MYLIBS_PWM_H_
#define INC_MYLIBS_PWM_H_

void pwm_start(void);
void set_pwm_alpha(int alpha);
void pwm_stop(void);

#define alpha_MAX 8500
#define PWM_MAX 100

#endif /* INC_MYLIBS_PWM_H_ */
