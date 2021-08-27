#ifndef RUNTIME_SIGNAL_HANDLERS_HPP
#define RUNTIME_SIGNAL_HANDLERS_HPP

namespace runtime {
/*!
 * Show stackdump on every incoming signal and exit with status -1.
 *
 * \note At this moment Unix only.
 */
void setup_signal_handlers();

}// namespace runtime

#endif// RUNTIME_SIGNAL_HANDLERS_HPP
