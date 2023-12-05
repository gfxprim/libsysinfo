#
# LIBSYSINFO specfile
#
# (C) Cyril Hrubis metan{at}ucw.cz 2023
#

Summary: A system information and statistic parser library
Name: libsysinfo
Version: git
Release: 1
License: LGPL-2.1-or-later
Group: System/Libraries
Url: https://github.com/gfxprim/libsysinfo
Source: libsysinfo-%{version}.tar.bz2

BuildRoot: %{_tmppath}/%{name}-%{version}-buildroot

%package -n libsysinfo1
Group: System/Libraries
Summary: A system information and statistic parser library

%package devel
Group: Development/Libraries/C and C++
Summary: Development files for libsysinfo library
Requires: libsysinfo1

%package -n sysinfo-tests
Group: System/Libraries
Summary: A system information and statistic parser library
Requires: libsysinfo1

%description
A system information and statistic parser library

%description -n libsysinfo1
A system information and statistic parser library

%description devel
A system information and statistic parser library

%description -n sysinfo-tests
A system information and statistic parser library test programs

%prep
%setup -n libsysinfo-%{version}

%build
./configure --prefix='/usr' --bindir=%{_bindir} --libdir=%{_libdir} --includedir=%{_includedir} --mandir=%{_mandir}
make %{?jobs:-j%jobs}

%install
DESTDIR="$RPM_BUILD_ROOT" make install

%files -n libsysinfo1
%defattr(-,root,root)
%{_libdir}/libsysinfo.so.1
%{_libdir}/libsysinfo.so.1.0.0

%files devel
%defattr(-,root,root)
%{_libdir}/libsysinfo.so
%{_libdir}/libsysinfo.a
%{_includedir}/sysinfo/
%{_includedir}/sysinfo/*.h

%files -n sysinfo-tests
%defattr(-,root,root)
%{_bindir}/*

%changelog
* Tue Dec  5 2023 Cyril Hrubis <metan@ucw.cz>

  Initial version.
