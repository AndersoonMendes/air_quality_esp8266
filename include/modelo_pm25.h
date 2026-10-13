


    // !!! This file is generated using emlearn !!!

    #include <stdint.h>
    

static inline int32_t modelo_pm25_tree_0(const int16_t *features, int32_t features_length) {
          if (features[0] < 123) {
              if (features[0] < 34) {
                  if (features[0] < 9) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[0] < 56) {
                      return 2;
                  } else {
                      return 3;
                  }
              }
          } else {
              return 4;
          }
        }
        

static inline int32_t modelo_pm25_tree_1(const int16_t *features, int32_t features_length) {
          if (features[0] < 35) {
              if (features[0] < 9) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[0] < 62) {
                  return 2;
              } else {
                  if (features[0] < 125) {
                      return 3;
                  } else {
                      return 4;
                  }
              }
          }
        }
        

static inline int32_t modelo_pm25_tree_2(const int16_t *features, int32_t features_length) {
          if (features[0] < 35) {
              if (features[0] < 10) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[0] < 56) {
                  return 2;
              } else {
                  if (features[0] < 123) {
                      return 3;
                  } else {
                      return 4;
                  }
              }
          }
        }
        

static inline int32_t modelo_pm25_tree_3(const int16_t *features, int32_t features_length) {
          if (features[0] < 35) {
              if (features[0] < 10) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[0] < 56) {
                  return 2;
              } else {
                  if (features[0] < 125) {
                      return 3;
                  } else {
                      return 4;
                  }
              }
          }
        }
        

static inline int32_t modelo_pm25_tree_4(const int16_t *features, int32_t features_length) {
          if (features[0] < 35) {
              if (features[0] < 9) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[0] < 56) {
                  return 2;
              } else {
                  if (features[0] < 125) {
                      return 3;
                  } else {
                      return 4;
                  }
              }
          }
        }
        

static inline int32_t modelo_pm25_tree_5(const int16_t *features, int32_t features_length) {
          if (features[0] < 35) {
              if (features[0] < 9) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[0] < 56) {
                  return 2;
              } else {
                  if (features[0] < 125) {
                      return 3;
                  } else {
                      return 4;
                  }
              }
          }
        }
        

static inline int32_t modelo_pm25_tree_6(const int16_t *features, int32_t features_length) {
          if (features[0] < 35) {
              if (features[0] < 10) {
                  return 0;
              } else {
                  return 1;
              }
          } else {
              if (features[0] < 56) {
                  return 2;
              } else {
                  if (features[0] < 125) {
                      return 3;
                  } else {
                      return 4;
                  }
              }
          }
        }
        

static inline int32_t modelo_pm25_tree_7(const int16_t *features, int32_t features_length) {
          if (features[0] < 56) {
              if (features[0] < 35) {
                  if (features[0] < 9) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  return 2;
              }
          } else {
              if (features[0] < 131) {
                  return 3;
              } else {
                  return 4;
              }
          }
        }
        

static inline int32_t modelo_pm25_tree_8(const int16_t *features, int32_t features_length) {
          if (features[0] < 125) {
              if (features[0] < 59) {
                  if (features[0] < 9) {
                      return 0;
                  } else {
                      if (features[0] < 35) {
                          return 1;
                      } else {
                          return 2;
                      }
                  }
              } else {
                  return 3;
              }
          } else {
              return 4;
          }
        }
        

static inline int32_t modelo_pm25_tree_9(const int16_t *features, int32_t features_length) {
          if (features[0] < 119) {
              if (features[0] < 35) {
                  if (features[0] < 9) {
                      return 0;
                  } else {
                      return 1;
                  }
              } else {
                  if (features[0] < 59) {
                      return 2;
                  } else {
                      return 3;
                  }
              }
          } else {
              return 4;
          }
        }
        

int32_t modelo_pm25_predict(const int16_t *features, int32_t features_length) {

        int32_t votes[5] = {0,};
        int32_t _class = -1;

        _class = modelo_pm25_tree_0(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_1(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_2(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_3(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_4(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_5(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_6(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_7(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_8(features, features_length); votes[_class] += 1;
    _class = modelo_pm25_tree_9(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<5; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    

int modelo_pm25_predict_proba(const int16_t *features, int32_t features_length, float *out, int out_length) {

        int32_t _class = -1;

        for (int i=0; i<out_length; i++) {
            out[i] = 0.0f;
        }

        _class = modelo_pm25_tree_0(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_1(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_2(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_3(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_4(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_5(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_6(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_7(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_8(features, features_length); out[_class] += 1.0f;
    _class = modelo_pm25_tree_9(features, features_length); out[_class] += 1.0f;
    
        // compute mean
        for (int i=0; i<out_length; i++) {
            out[i] = out[i] / 10;
        }
        return 0;
    }
    