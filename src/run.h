/** @file */
#ifndef TP_RUN_H
#define TP_RUN_H

namespace csmp {
namespace tperm {
class Settings;

/// Forwards settings from file
void run(const char *);

/// Main control flow method
void run(const Settings &);

} // !tperm
} // !csmp

#endif // !TP_RUN_H