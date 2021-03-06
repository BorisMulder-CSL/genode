/*
 * \brief  Hook functions for bootstrapping a libc-using Genode component
 * \author Norman Feske
 * \date   2016-12-23
 *
 * This interface is implemented by components that use both Genode's API and
 * the libc. For such components, the libc provides the 'Component::construct'
 * function that takes the precautions needed for letting the application use
 * blocking I/O via POSIX functions like 'read' or 'select'. The libc's
 * 'Component::construct' function finally passes control to the application by
 * calling the application-provided 'Libc::Component::construct' function.
 */

/*
 * Copyright (C) 2016 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _INCLUDE__LIBC__COMPONENT_H_
#define _INCLUDE__LIBC__COMPONENT_H_

#include <vfs/file_system.h>
#include <base/env.h>
#include <base/stdint.h>


/**
 * Interface to be provided by the component implementation
 */
namespace Libc {

	class Env : public Genode::Env
	{
		private:

			virtual Genode::Xml_node _config_xml() const = 0;

		public:

			/**
			 * Component configuration
			 */
			template <typename FUNC>
			void config(FUNC const &func) const {
				func(_config_xml()); }

			/**
			 * Virtual File System configured for this component
			 */
			virtual Vfs::File_system &vfs() = 0;
	};

	namespace Component {

		/**
		 * Return stack size of the component's initial entrypoint
		 */
		Genode::size_t stack_size();

		/**
		 * Construct component
		 *
		 * \param env  extended interface to the component's execution environment
		 */
		void construct(Libc::Env &env);
	}
}

#endif /* _INCLUDE__LIBC__COMPONENT_H_ */
